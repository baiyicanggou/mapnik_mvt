package mapnik

// #include <stdlib.h>
// #include "raster_c_api.h"
// #cgo CFLAGS: -I ./
// #cgo CXXFLAGS: -I -std=c++14
import "C"
import "unsafe"

type RasterType int

var (
	RASTER_DTYPE_RGBA8   = RasterType(C.RASTER_DTYPE_RGBA8)
	RASTER_DTYPE_GRAY8   = RasterType(C.RASTER_DTYPE_GRAY8)
	RASTER_DTYPE_GRAY8S  = RasterType(C.RASTER_DTYPE_GRAY8S)
	RASTER_DTYPE_GRAY16  = RasterType(C.RASTER_DTYPE_GRAY16)
	RASTER_DTYPE_GRAY16S = RasterType(C.RASTER_DTYPE_GRAY16S)
	RASTER_DTYPE_GRAY32  = RasterType(C.RASTER_DTYPE_GRAY32)
	RASTER_DTYPE_GRAY32S = RasterType(C.RASTER_DTYPE_GRAY32S)
	RASTER_DTYPE_GRAY32F = RasterType(C.RASTER_DTYPE_GRAY32F)
	RASTER_DTYPE_GRAY64  = RasterType(C.RASTER_DTYPE_GRAY64)
	RASTER_DTYPE_GRAY64S = RasterType(C.RASTER_DTYPE_GRAY64S)
	RASTER_DTYPE_GRAY64F = RasterType(C.RASTER_DTYPE_GRAY64F)
)

type Raster struct {
	m *C.struct__mapnik_raster_t
}

func (r *Raster) Free() {
	C.mapnik_raster_free(r.m)
	r.m = nil
}

func (r *Raster) Type() RasterType {
	return RasterType(C.mapnik_raster_type(r.m))
}

func NewRaster(width, height int, tp RasterType, data []byte) *Raster {
	rst := &Raster{m: C.mapnik_raster_new(C.int(width), C.int(height), C.int(tp))}
	C.mapnik_raster_copy_data(rst.m, (*C.uchar)(unsafe.Pointer(&data[0])), C.int(len(data)))
	return rst
}

type RasterData struct {
	m *C.struct__mapnik_raster_data_t
}

func (r *RasterData) Free() {
	C.mapnik_raster_data_free(r.m)
	r.m = nil
}

func NewRasterData(width, height int, tp RasterType, data []byte, bbox [4]float64, tileSize int) *RasterData {
	rst := NewRaster(width, height, tp, data)
	defer rst.Free()
	return &RasterData{m: C.mapnik_raster_data_new(rst.m, (*C.double)(unsafe.Pointer(&data[0])), C.uint(tileSize))}
}

type RasterTiledData struct {
	m *C.struct__mapnik_raster_tiled_data_t
}

func (r *RasterTiledData) Free() {
	C.mapnik_raster_tiled_data_free(r.m)
	r.m = nil
}

func NewRasterTiledData(rs [][]RasterData, tileSize int) *RasterTiledData {
	row := len(rs[0])
	col := len(rs)
	out := make([]*C.struct__mapnik_raster_data_t, row*col)
	for j := 0; j < row; j++ {
		for i := 0; i < col; i++ {
			out[j*col+i] = rs[j][i].m
		}
	}
	return &RasterTiledData{m: C.mapnik_raster_tiled_data_new((**C.struct__mapnik_raster_data_t)(unsafe.Pointer(&out[0])), C.uint(row), C.uint(col), C.uint(tileSize))}
}
