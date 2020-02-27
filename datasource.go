package mapnik

// #include <stdlib.h>
// #include "datasource_c_api.h"
// #cgo CFLAGS: -I ./ -I ./external/mapnik/include
// #cgo CXXFLAGS:  -I ./  -I ./external/mapnik/include -I -std=c++14
import "C"
import "unsafe"

type DatasourceType int

var (
	DatasourceVector = DatasourceType(C.DATASOURCE_VECTOR)
	DatasourceRaster = DatasourceType(C.DATASOURCE_RASTER)
)

type Datasource struct {
	m *C.struct__mapnik_datasource_t
}

func (d *Datasource) Free() {
	C.mapnik_datasource_free(d.m)
	d.m = nil
}

func (d *Datasource) Type() DatasourceType {
	return DatasourceType(C.mapnik_datasource_type(d.m))
}

func (d *Datasource) Envelope() [4]float64 {
	var ret [4]float64
	C.mapnik_datasource_envelope(d.m, (*C.double)(unsafe.Pointer(&ret[0])))
	return ret
}

func NewVectorDatasource(fc *FeatureCollection) *Datasource {
	return &Datasource{m: C.mapnik_geometry_datasource(fc.m)}
}

func NewRasterDatasource(rs *RasterData) *Datasource {
	return &Datasource{m: C.mapnik_raster_datasource(rs.m)}
}

func NewTiledRasterDatasource(rs *RasterTiledData) *Datasource {
	return &Datasource{m: C.mapnik_tiled_raster_datasource(rs.m)}
}
