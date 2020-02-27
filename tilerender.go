package mapnik

// #include <stdlib.h>
// #include "tilerender_c_api.h"
// #cgo CFLAGS: -I ./
// #cgo CXXFLAGS: -I -std=c++14
import "C"

import (
	"bytes"
	"image"
	"image/png"
	"unsafe"
)

type Tile struct {
	m *C.struct__mapnik_tile_t
}

type TileData struct {
	Image image.Image
	X     uint32
	Y     uint32
	Z     uint32
}

func (r *Tile) Free() {
	C.mapnik_tile_free(r.m)
	r.m = nil
}

func (r *Tile) Count() int {
	return int(C.mapnik_tile_data_count(r.m))
}

func (r *Tile) GetAllData() []*TileData {
	out := make([]*TileData, r.Count())
	for i := range out {
		out[i], _ = r.GetData(i)
	}
	return out
}

func (r *Tile) GetData(i int) (*TileData, error) {
	var size int
	var data TileData
	raw := C.mapnik_tile_get_data(r.m, C.int(i), (*C.int)(unsafe.Pointer(&size)), (*C.uint)(unsafe.Pointer(&data.X)), (*C.uint)(unsafe.Pointer(&data.Y)), (*C.uint)(unsafe.Pointer(&data.Z)))
	b := C.GoBytes(unsafe.Pointer(raw), C.int(size))
	img, err := png.Decode(bytes.NewBuffer(b))
	if err != nil {
		return nil, err
	}
	data.Image = img
	return &data, nil
}

func NewTile(x, y, z, width, height uint32) *Tile {
	return &Tile{m: C.mapnik_tile(C.uint(x), C.uint(y), C.uint(z), C.uint(width), C.uint(height))}
}

type MvtTile struct {
	m *C.struct__mvt_tile_t
}

type MvtTileData struct {
	Data []uint8
	X    uint32
	Y    uint32
	Z    uint32
}

func (r *MvtTile) Free() {
	C.mvt_tile_free(r.m)
	r.m = nil
}

func (r *MvtTile) Count() int {
	return int(C.mvt_tile_data_count(r.m))
}

func (r *MvtTile) GetAllData() []*MvtTileData {
	out := make([]*MvtTileData, r.Count())
	for i := range out {
		out[i], _ = r.GetData(i)
	}
	return out
}

func (r *MvtTile) GetData(i int) (*MvtTileData, error) {
	var size int
	var data MvtTileData
	raw := C.mvt_tile_get_data(r.m, C.int(i), (*C.int)(unsafe.Pointer(&size)), (*C.uint)(unsafe.Pointer(&data.X)), (*C.uint)(unsafe.Pointer(&data.Y)), (*C.uint)(unsafe.Pointer(&data.Z)))
	b := C.GoBytes(unsafe.Pointer(raw), C.int(size))
	data.Data = b
	return &data, nil
}

func NewMvtTile(x, y, z, width, height uint32) *MvtTile {
	return &MvtTile{m: C.mvt_tile(C.uint(x), C.uint(y), C.uint(z), C.uint(width), C.uint(height))}
}


type UtfgridTile struct {
	m *C.struct__utfgrid_tile_t
}

type UtfgridTileData struct {
	Data []uint8
	X    uint32
	Y    uint32
	Z    uint32
}

func (r *UtfgridTile) Free() {
	C.utfgrid_tile_free(r.m)
	r.m = nil
}

func (r *UtfgridTile) Count() int {
	return int(C.utfgrid_tile_data_count(r.m))
}

func (r *UtfgridTile) GetAllData() []*UtfgridTileData {
	out := make([]*UtfgridTileData, r.Count())
	for i := range out {
		out[i], _ = r.GetData(i)
	}
	return out
}

func (r *UtfgridTile) GetData(i int) (*UtfgridTileData, error) {
	var size int
	var data UtfgridTileData
	raw := C.utfgrid_tile_get_data(r.m, C.int(i), (*C.int)(unsafe.Pointer(&size)), (*C.uint)(unsafe.Pointer(&data.X)), (*C.uint)(unsafe.Pointer(&data.Y)), (*C.uint)(unsafe.Pointer(&data.Z)))
	b := C.GoBytes(unsafe.Pointer(raw), C.int(size))
	data.Data = b
	return &data, nil
}

func NewUtfgridTile(x, y, z, width, height uint32) *UtfgridTile {
	return &UtfgridTile{m: C.utfgrid_tile(C.uint(x), C.uint(y), C.uint(z), C.uint(width), C.uint(height))}
}
