package mapnik

// #include <stdlib.h>
// #include "tiler_c_api.h"
// #cgo CFLAGS: -I ./
// #cgo CXXFLAGS: -I -std=c++14
import "C"
import "unsafe"

type TilerGrid struct {
	m *C.struct__tiler_grid_t
}

func (r *TilerGrid) Free() {
	C.tiler_grid_free(r.m)
	r.m = nil
}

func NewGlobalGeodeticGrid(tileSize uint32) *TilerGrid {
	return &TilerGrid{m: C.tiler_global_geodetic_grid(C.uint(tileSize))}
}

func NewGlobalMercatorGrid(tileSize uint32) *TilerGrid {
	return &TilerGrid{m: C.tiler_global_mercator_grid(C.uint(tileSize))}
}

func NewGeodeticGrid(tileSize uint32, box [4]float64) *TilerGrid {
	return &TilerGrid{m: C.tiler_geodetic_grid(C.uint(tileSize), (*C.double)(unsafe.Pointer(&box[0])))}
}

func NewMercatorGrid(tileSize uint32, box [4]float64) *TilerGrid {
	return &TilerGrid{m: C.tiler_mercator_grid(C.uint(tileSize), (*C.double)(unsafe.Pointer(&box[0])))}
}

type TilerSource struct {
	m *C.struct__tiler_source_t
}

func (r *TilerSource) Free() {
	C.tiler_source_free(r.m)
	r.m = nil
}

func (r *TilerSource) AddDatasource(name string, ds Datasource) {
	kname := C.CString(name)
	defer C.free(unsafe.Pointer(kname))
	C.tiler_source_add_datasource(r.m, kname, ds.m)
}

func NewTilerSource(maps map[string]Map) *TilerSource {
	opts := C.tiler_source_options_new()
	for k, m := range maps {
		kname := C.CString(k)
		defer C.free(unsafe.Pointer(kname))
		C.tiler_source_options_add(opts, kname, m.m)
	}
	defer C.tiler_source_options_free(opts)

	return &TilerSource{m: C.tiler_source_new(opts)}
}

type Tiler struct {
	m *C.struct__mapnik_tiler_t
}

func (r *Tiler) Free() {
	C.mapnik_tiler_free(r.m)
	r.m = nil
}

type writerContext struct {
	cb func(*Tile)
}

func (r *Tiler) Render(start, end uint32, cb func(*Tile)) {
	C.mapnik_tiler_render(r.m, C.uint(start), C.uint(end), unsafe.Pointer(&writerContext{cb: cb}))
}

func (r *Tiler) RenderForSelect(selects []uint16, cb func(*Tile)) {
	C.mapnik_tiler_render_select(r.m, (*C.ushort)(unsafe.Pointer(&selects[0])), C.int(len(selects)), unsafe.Pointer(&writerContext{cb: cb}))
}

//export writeTileFunc
func writeTileFunc(p unsafe.Pointer, t *C.struct__mapnik_tile_t) {
	ctx := (*writerContext)(p)
	tile := &Tile{m: t}
	ctx.cb(tile)
}

func NewTiler(style string, layer []string, source *TilerSource, grid *TilerGrid) *Tiler {
	kstyle := C.CString(style)
	defer C.free(unsafe.Pointer(kstyle))
	opts := C.mapnik_tiler_options_new(kstyle)
	for i := range layer {
		kname := C.CString(layer[i])
		defer C.free(unsafe.Pointer(kname))
		C.mapnik_tiler_options_add_layer(opts, kname)
	}
	defer C.mapnik_tiler_options_free(opts)
	return &Tiler{m: C.mapnik_tiler_new(source.m, grid.m, opts)}
}

type MvtTiler struct {
	m *C.struct__mvt_tiler_t
}

func (r *MvtTiler) Free() {
	C.mvt_tiler_free(r.m)
	r.m = nil
}

type writerMvtContext struct {
	cb func(*MvtTile)
}

func (r *MvtTiler) Render(start, end uint32, cb func(*MvtTile)) {
	C.mvt_tiler_render(r.m, C.uint(start), C.uint(end), unsafe.Pointer(&writerMvtContext{cb: cb}))
}

func (r *MvtTiler) RenderForSelect(selects []uint16, cb func(*MvtTile)) {
	C.mvt_tiler_render_select(r.m, (*C.ushort)(unsafe.Pointer(&selects[0])), C.int(len(selects)), unsafe.Pointer(&writerMvtContext{cb: cb}))
}

//export writeMvtTileFunc
func writeMvtTileFunc(p unsafe.Pointer, t *C.struct__mvt_tile_t) {
	ctx := (*writerMvtContext)(p)
	tile := &MvtTile{m: t}
	ctx.cb(tile)
}

func NewMvtTiler(style string, layer []string, source *TilerSource, grid *TilerGrid) *MvtTiler {
	kstyle := C.CString(style)
	defer C.free(unsafe.Pointer(kstyle))
	opts := C.mvt_tiler_options_new(kstyle)
	for i := range layer {
		kname := C.CString(layer[i])
		defer C.free(unsafe.Pointer(kname))
		C.mvt_tiler_options_add_layer(opts, kname)
	}
	defer C.mvt_tiler_options_free(opts)
	return &MvtTiler{m: C.mvt_tiler_new(source.m, grid.m, opts)}
}

type UtfgridTiler struct {
	m *C.struct__utfgrid_tiler_t
}

func (r *UtfgridTiler) Free() {
	C.utfgrid_tiler_free(r.m)
	r.m = nil
}

type writerUtfgridContext struct {
	cb func(*UtfgridTile)
}

func (r *UtfgridTiler) Render(start, end uint32, cb func(*UtfgridTile)) {
	C.utfgrid_tiler_render(r.m, C.uint(start), C.uint(end), unsafe.Pointer(&writerUtfgridContext{cb: cb}))
}

func (r *UtfgridTiler) RenderForSelect(selects []uint16, cb func(*UtfgridTile)) {
	C.utfgrid_tiler_render_select(r.m, (*C.ushort)(unsafe.Pointer(&selects[0])), C.int(len(selects)), unsafe.Pointer(&writerUtfgridContext{cb: cb}))
}

//export writeUtfgridTileFunc
func writeUtfgridTileFunc(p unsafe.Pointer, t *C.struct__utfgrid_tile_t) {
	ctx := (*writerUtfgridContext)(p)
	tile := &UtfgridTile{m: t}
	ctx.cb(tile)
}

func NewUtfgridTiler(style string, layer []string, source *TilerSource, grid *TilerGrid) *UtfgridTiler {
	kstyle := C.CString(style)
	defer C.free(unsafe.Pointer(kstyle))
	opts := C.utfgrid_tiler_options_new(kstyle)
	for i := range layer {
		kname := C.CString(layer[i])
		defer C.free(unsafe.Pointer(kname))
		C.utfgrid_tiler_options_add_layer(opts, kname)
	}
	defer C.utfgrid_tiler_options_free(opts)
	return &UtfgridTiler{m: C.utfgrid_tiler_new(source.m, grid.m, opts)}
}
