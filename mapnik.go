package mapnik

// #include <stdlib.h>
// #include "mapnik_c_api.h"
// #cgo CFLAGS:  -I ./
// #cgo linux CXXFLAGS: -I ./external/mapnik/include -I ./external/harfbuzz/include  -I ./external/libboost/boost_1_67_0 -I ./external/mapnik/deps  -I ./external/mapnik/deps/agg/include  -I ./external/mapnik/deps/mapbox/variant/include  -I ./external/icu/source/common -I ./external/mapnik/vector_tile/protozero/include -I ./external/zlib -I ./build/external/zlib -I ./external/rapidjson/include  -I ./external/mapnik/vector_tile/src -I ./external/mapnik/vector_tile/geometry/include  -std=c++14
// #cgo darwin CXXFLAGS: -I ./external/mapnik/include -I ./external/harfbuzz/include  -I ./libboost/boost_1_67_0 -I ./external/mapnik/deps  -I ./external/mapnik/deps/agg/include  -I ./external/mapnik/deps/mapbox/variant/include  -I ./external/icu/source/common -I ./external/mapnik/vector_tile/protozero/include -I ./external/zlib -I ./build/external/zlib -I ./external/rapidjson/include -I ./external/mapnik/vector_tile/src -I ./external/mapnik/vector_tile/geometry/include  -std=gnu++14
// #cgo darwin LDFLAGS: -L ./libs -lmapnik  -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -lexpat -licutools -licui18n -licudt -licudata  -lwebp  -lpng -ljpeg -lxml2  -lproj -lmapnik_vector_tile -lzlib -lpixman -lcairo -lharfbuzz -lfreetype
// #cgo linux LDFLAGS: -L ./libs -Wl,--start-group -lmapnik  -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -lexpat -licutools -licui18n -licudt -licudata  -lwebp  -lpng -ljpeg -lxml2  -lproj -lmapnik_vector_tile -lzlib -lpixman -lcairo -lharfbuzz -lfreetype -Wl,--end-group
import "C"

import (
	"errors"
	"fmt"
	"image"
	"image/color"
	"image/draw"
	"io/ioutil"
	"os"
	"path/filepath"
	"strings"
	"unsafe"
)

type LogLevel int

var (
	None  = LogLevel(C.MAPNIK_NONE)
	Debug = LogLevel(C.MAPNIK_DEBUG)
	Warn  = LogLevel(C.MAPNIK_WARN)
	Error = LogLevel(C.MAPNIK_ERROR)
)

var (
	fontPath   = "/usr/lib/mapnik/3.0/fonts"
	pluginPath = "/usr/lib/mapnik/3.0/input"
)

func init() {
	if err := RegisterDatasources(pluginPath); err != nil {
		fmt.Fprintf(os.Stderr, "MAPNIK: %s\n", err)
	}
	if err := RegisterFonts(fontPath); err != nil {
		fmt.Fprintf(os.Stderr, "MAPNIK: %s\n", err)
	}
}

func RegisterDatasources(path string) error {
	fileInfos, err := ioutil.ReadDir(path)
	if err != nil {
		return err
	}

	for _, file := range fileInfos {
		cs := C.CString(filepath.Join(path, file.Name()))
		defer C.free(unsafe.Pointer(cs))
		if C.mapnik_register_datasource(cs) == 0 {
			e := C.GoString(C.mapnik_register_last_error())
			if e != "" {
				return errors.New("registering datasources: " + e)
			}
			return errors.New("error while registering datasources")
		}
	}
	return nil
}

func RegisterFonts(path string) error {
	fileInfos, err := ioutil.ReadDir(path)
	if err != nil {
		return err
	}

	for _, file := range fileInfos {
		fullPath := filepath.Join(path, file.Name())
		if !isFontFile(fullPath) {
			continue
		}
		cs := C.CString(fullPath)
		defer C.free(unsafe.Pointer(cs))
		if C.mapnik_register_font(cs) == 0 {
			e := C.GoString(C.mapnik_register_last_error())
			if e != "" {
				return errors.New("registering fonts: " + e)
			}
			return errors.New("error while registering fonts")
		}
	}
	return nil
}

func isFontFile(path string) bool {
	ext := strings.ToLower(filepath.Ext(path))
	return (ext == ".ttf" ||
		ext == ".otf" ||
		ext == ".woff" ||
		ext == ".ttc" ||
		ext == ".pfa" ||
		ext == ".pfb" ||
		ext == ".dfont")
}

func LogSeverity(level LogLevel) {
	C.mapnik_logging_set_severity(C.int(level))
}

type version struct {
	Numeric int
	Major   int
	Minor   int
	Patch   int
	String  string
}

var Version version

func init() {
	Version.Numeric = int(C.mapnik_version)
	Version.Major = int(C.mapnik_version_major)
	Version.Minor = int(C.mapnik_version_minor)
	Version.Patch = int(C.mapnik_version_patch)
	Version.String = fmt.Sprintf("%d.%d.%d", Version.Major, Version.Minor, Version.Patch)
}

type Map struct {
	m           *C.struct__mapnik_map_t
	width       int
	height      int
	layerStatus []bool
}

func New() *Map {
	return &Map{
		m:      C.mapnik_map(C.uint(800), C.uint(600)),
		width:  800,
		height: 600,
	}
}

func NewSized(width, height int) *Map {
	return &Map{
		m:      C.mapnik_map(C.uint(width), C.uint(height)),
		width:  width,
		height: height,
	}
}

func (m *Map) lastError() error {
	return errors.New("mapnik: " + C.GoString(C.mapnik_map_last_error(m.m)))
}

func (m *Map) LoadString(str string) error {
	cs := C.CString(str)
	defer C.free(unsafe.Pointer(cs))
	if C.mapnik_map_load_string(m.m, cs) != 0 {
		return m.lastError()
	}

	C.mapnik_apply_layer_off_hack(m.m)
	return nil
}

func (m *Map) Load(stylesheet string) error {
	cs := C.CString(stylesheet)
	defer C.free(unsafe.Pointer(cs))
	if C.mapnik_map_load(m.m, cs) != 0 {
		return m.lastError()
	}

	C.mapnik_apply_layer_off_hack(m.m)
	return nil
}

func (m *Map) Resize(width, height int) {
	C.mapnik_map_resize(m.m, C.uint(width), C.uint(height))
	m.width = width
	m.height = height
}

func (m *Map) Free() {
	C.mapnik_map_free(m.m)
	m.m = nil
}

func (m *Map) SRS() string {
	return C.GoString(C.mapnik_map_get_srs(m.m))
}

func (m *Map) SetSRS(srs string) {
	cs := C.CString(srs)
	defer C.free(unsafe.Pointer(cs))
	C.mapnik_map_set_srs(m.m, cs)
}

func (m *Map) ScaleDenominator() float64 {
	return float64(C.mapnik_map_get_scale_denominator(m.m))
}

func (m *Map) ZoomAll() error {
	if C.mapnik_map_zoom_all(m.m) != 0 {
		return m.lastError()
	}
	return nil
}

func (m *Map) ZoomTo(minx, miny, maxx, maxy float64) {
	bbox := C.mapnik_bbox(C.double(minx), C.double(miny), C.double(maxx), C.double(maxy))
	defer C.mapnik_bbox_free(bbox)
	C.mapnik_map_zoom_to_box(m.m, bbox)
}

func (m *Map) BackgroundColor() color.NRGBA {
	c := color.NRGBA{}
	C.mapnik_map_background(m.m, (*C.uint8_t)(&c.R), (*C.uint8_t)(&c.G), (*C.uint8_t)(&c.B), (*C.uint8_t)(&c.A))
	return c
}

func (m *Map) SetBackgroundColor(c color.NRGBA) {
	C.mapnik_map_set_background(m.m, C.uint8_t(c.R), C.uint8_t(c.G), C.uint8_t(c.B), C.uint8_t(c.A))
}

func (m *Map) RemoveAllLayer() {
	C.mapnik_map_layer_remove_all(m.m)
}

func (m *Map) AddLayer(l *Layer) {
	C.mapnik_map_layer_add_layer(m.m, l.m)
}

func (m *Map) printLayerStatus() {
	n := C.mapnik_map_layer_count(m.m)
	for i := 0; i < int(n); i++ {
		fmt.Println(
			C.GoString(C.mapnik_map_layer_name(m.m, C.size_t(i))),
			C.mapnik_map_layer_is_active(m.m, C.size_t(i)),
		)
	}
}

func (m *Map) storeLayerStatus() {
	if len(m.layerStatus) > 0 {
		return
	}
	m.layerStatus = m.currentLayerStatus()
}

func (m *Map) currentLayerStatus() []bool {
	n := C.mapnik_map_layer_count(m.m)
	active := make([]bool, n)
	for i := 0; i < int(n); i++ {
		if C.mapnik_map_layer_is_active(m.m, C.size_t(i)) == 1 {
			active[i] = true
		}
	}
	return active
}

func (m *Map) resetLayerStatus() {
	if len(m.layerStatus) == 0 {
		return
	}
	n := C.mapnik_map_layer_count(m.m)
	if int(n) > len(m.layerStatus) {
		return
	}
	for i := 0; i < int(n); i++ {
		if m.layerStatus[i] {
			C.mapnik_map_layer_set_active(m.m, C.size_t(i), 1)
		} else {
			C.mapnik_map_layer_set_active(m.m, C.size_t(i), 0)
		}
	}
	m.layerStatus = nil
}

type Status int

const (
	Exclude Status = -1
	Default Status = 0
	Include Status = 1
)

type LayerSelector interface {
	Select(layername string) Status
}

type SelectorFunc func(string) Status

func (f SelectorFunc) Select(layername string) Status {
	return f(layername)
}

func (m *Map) SelectLayers(selector LayerSelector) bool {
	m.storeLayerStatus()
	selected := false
	n := C.mapnik_map_layer_count(m.m)
	for i := 0; i < int(n); i++ {
		layerName := C.GoString(C.mapnik_map_layer_name(m.m, C.size_t(i)))
		switch selector.Select(layerName) {
		case Include:
			selected = true
			C.mapnik_map_layer_set_active(m.m, C.size_t(i), 1)
		case Exclude:
			C.mapnik_map_layer_set_active(m.m, C.size_t(i), 0)
		case Default:
			selected = true
		}
	}
	return selected
}

func (m *Map) ResetLayers() {
	m.resetLayerStatus()
}

func (m *Map) SetMaxExtent(minx, miny, maxx, maxy float64) {
	C.mapnik_map_set_maximum_extent(m.m, C.double(minx), C.double(miny), C.double(maxx), C.double(maxy))
}

func (m *Map) ResetMaxExtent() {
	C.mapnik_map_reset_maximum_extent(m.m)
}

type RenderOpts struct {
	Scale       float64
	ScaleFactor float64
	Format      string
}

func (m *Map) Render(opts RenderOpts) ([]byte, error) {
	scaleFactor := opts.ScaleFactor
	if scaleFactor == 0.0 {
		scaleFactor = 1.0
	}
	i := C.mapnik_map_render_to_image(m.m, C.double(opts.Scale), C.double(scaleFactor))
	if i == nil {
		return nil, m.lastError()
	}
	defer C.mapnik_image_free(i)
	if opts.Format == "raw" {
		size := 0
		raw := C.mapnik_image_to_raw(i, (*C.size_t)(unsafe.Pointer(&size)))
		return C.GoBytes(unsafe.Pointer(raw), C.int(size)), nil
	}
	var format *C.char
	if opts.Format != "" {
		format = C.CString(opts.Format)
	} else {
		format = C.CString("png256")
	}
	b := C.mapnik_image_to_blob(i, format)
	if b == nil {
		return nil, errors.New("mapnik: " + C.GoString(C.mapnik_image_last_error(i)))
	}
	C.free(unsafe.Pointer(format))
	defer C.mapnik_image_blob_free(b)
	return C.GoBytes(unsafe.Pointer(b.ptr), C.int(b.len)), nil
}

func (m *Map) RenderImage(opts RenderOpts) (*image.NRGBA, error) {
	scaleFactor := opts.ScaleFactor
	if scaleFactor == 0.0 {
		scaleFactor = 1.0
	}
	i := C.mapnik_map_render_to_image(m.m, C.double(opts.Scale), C.double(scaleFactor))
	if i == nil {
		return nil, m.lastError()
	}
	defer C.mapnik_image_free(i)
	size := 0
	raw := C.mapnik_image_to_raw(i, (*C.size_t)(unsafe.Pointer(&size)))
	b := C.GoBytes(unsafe.Pointer(raw), C.int(size))
	img := &image.NRGBA{
		Pix:    b,
		Stride: int(m.width * 4),
		Rect:   image.Rect(0, 0, int(m.width), int(m.height)),
	}
	return img, nil
}

func (m *Map) RenderToFile(opts RenderOpts, path string) error {
	scaleFactor := opts.ScaleFactor
	if scaleFactor == 0.0 {
		scaleFactor = 1.0
	}
	cs := C.CString(path)
	defer C.free(unsafe.Pointer(cs))
	var format *C.char
	if opts.Format != "" {
		format = C.CString(opts.Format)
	} else {
		format = C.CString("png256")
	}
	defer C.free(unsafe.Pointer(format))
	if C.mapnik_map_render_to_file(m.m, cs, C.double(opts.Scale), C.double(scaleFactor), format) != 0 {
		return m.lastError()
	}
	return nil
}

func (m *Map) RenderToTile(tile *Tile, buffSize, tileSize uint32) error {
	C.mapnik_map_render_to_tile(m.m, tile.m, C.int(buffSize), C.int(tileSize))
	return nil
}

func (m *Map) RenderToMvtTile(tile *MvtTile, buffSize, tileSize uint32) error {
	C.mvt_map_render_to_tile(m.m, tile.m, C.int(buffSize), C.int(tileSize))
	return nil
}

func (m *Map) RenderToUtfgridTile(tile *UtfgridTile, key string, buffSize uint32) error {
	k := C.CString(key)
	defer C.free(unsafe.Pointer(k))
	C.utfgrid_map_render_to_tile(m.m, tile.m, k, C.int(buffSize))
	return nil
}

func (m *Map) SetBufferSize(s int) {
	C.mapnik_map_set_buffer_size(m.m, C.int(s))
}

func Encode(img image.Image, format string) ([]byte, error) {
	tmp := toNRGBA(img)
	i := C.mapnik_image_from_raw(
		(*C.uint8_t)(unsafe.Pointer(&tmp.Pix[0])),
		C.int(tmp.Bounds().Dx()),
		C.int(tmp.Bounds().Dy()),
	)
	defer C.mapnik_image_free(i)

	cformat := C.CString(format)
	b := C.mapnik_image_to_blob(i, cformat)
	if b == nil {
		return nil, errors.New("mapnik: " + C.GoString(C.mapnik_image_last_error(i)))
	}
	C.free(unsafe.Pointer(cformat))
	defer C.mapnik_image_blob_free(b)
	return C.GoBytes(unsafe.Pointer(b.ptr), C.int(b.len)), nil
}

func toNRGBA(src image.Image) *image.NRGBA {
	switch src := src.(type) {
	case *image.NRGBA:
		return src
	case *image.RGBA:
		result := image.NewNRGBA(src.Bounds())
		drawRGBAOver(result, result.Bounds(), src, image.ZP)
		return result
	default:
		result := image.NewNRGBA(src.Bounds())
		draw.Draw(result, result.Bounds(), src, image.ZP, draw.Over)
		return result
	}
}

func drawRGBAOver(dst *image.NRGBA, r image.Rectangle, src *image.RGBA, sp image.Point) {
	i0 := (r.Min.X - dst.Rect.Min.X) * 4
	i1 := (r.Max.X - dst.Rect.Min.X) * 4
	si0 := (sp.X - src.Rect.Min.X) * 4
	yMax := r.Max.Y - dst.Rect.Min.Y

	y := r.Min.Y - dst.Rect.Min.Y
	sy := sp.Y - src.Rect.Min.Y
	for ; y != yMax; y, sy = y+1, sy+1 {
		dpix := dst.Pix[y*dst.Stride:]
		spix := src.Pix[sy*src.Stride:]

		for i, si := i0, si0; i < i1; i, si = i+4, si+4 {
			sr := spix[si+0]
			sg := spix[si+1]
			sb := spix[si+2]
			sa := spix[si+3]

			if sa == 0xff {
				dpix[i+0] = sr
				dpix[i+1] = sg
				dpix[i+2] = sb
			} else if sa == 0x00 {
				dpix[i+0] = 0
				dpix[i+1] = 0
				dpix[i+2] = 0
			} else {
				dpix[i+0] = uint8(((uint32(sr) * 0xffff) / uint32(sa)) >> 8)
				dpix[i+1] = uint8(((uint32(sg) * 0xffff) / uint32(sa)) >> 8)
				dpix[i+2] = uint8(((uint32(sb) * 0xffff) / uint32(sa)) >> 8)
			}
			dpix[i+3] = sa
		}
	}
}

type Layer struct {
	m *C.struct__mapnik_layer_t
}

func (f *Layer) Free() {
	C.mapnik_layer_free(f.m)
	f.m = nil
}

func (f *Layer) AddStyle(style string) {
	stylestr := C.CString(style)
	defer C.free(unsafe.Pointer(stylestr))
	C.mapnik_layer_add_style(f.m, stylestr)
}

func (f *Layer) SetVirtualDatasource(ds string) {
	dsname := C.CString(ds)
	defer C.free(unsafe.Pointer(dsname))
	C.mapnik_layer_set_virtual_datasource(f.m, dsname)
}

func (f *Layer) SetDatasource(ds *Datasource) {
	C.mapnik_layer_set_datasource(f.m, ds.m)
}

func (f *Layer) SetName(name string) {
	namestr := C.CString(name)
	defer C.free(unsafe.Pointer(namestr))
	C.mapnik_layer_set_name(f.m, namestr)
}

func (f *Layer) SetSrs(srs string) {
	srsstr := C.CString(srs)
	defer C.free(unsafe.Pointer(srsstr))
	C.mapnik_layer_set_srs(f.m, srsstr)
}

func (f *Layer) GetName() string {
	return C.GoString(C.mapnik_layer_get_name(f.m))
}

func (f *Layer) GetSrs() string {
	return C.GoString(C.mapnik_layer_get_srs(f.m))
}

func (f *Layer) SetMinZoom(v float64) {
	C.mapnik_layer_set_min_zoom(f.m, C.double(v))
}

func (f *Layer) SetMaxZoom(v float64) {
	C.mapnik_layer_set_max_zoom(f.m, C.double(v))
}

func (f *Layer) GetMinZoom() float64 {
	return float64(C.mapnik_layer_get_min_zoom(f.m))
}

func (f *Layer) GetMaxZoom() float64 {
	return float64(C.mapnik_layer_get_max_zoom(f.m))
}

func (f *Layer) SetMaxExtent(bbox [4]float64) {
	cbbox := C.mapnik_bbox(C.double(bbox[0]), C.double(bbox[1]), C.double(bbox[2]), C.double(bbox[3]))
	defer C.mapnik_bbox_free(cbbox)
	C.mapnik_layer_set_max_extent(f.m, cbbox)
}

func (f *Layer) GetMaxExtent() [4]float64 {
	var b [4]float64
	C.mapnik_layer_get_max_extent(f.m, (*C.double)(unsafe.Pointer(&b[0])))
	return b
}

func NewLayer(name string, srs string) *Layer {
	namestr := C.CString(name)
	defer C.free(unsafe.Pointer(namestr))
	srsstr := C.CString(srs)
	defer C.free(unsafe.Pointer(srsstr))
	return &Layer{m: C.mapnik_layer(namestr, srsstr)}
}
