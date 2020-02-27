package mapnik

// #include <stdlib.h>
// #include "feature_c_api.h"
// #cgo CFLAGS: -I ./
// #cgo CXXFLAGS: -I -std=c++14
import "C"

func NewIdentifier(t interface{}) *Identifier {
	switch v := t.(type) {
	case uint64:
		return &Identifier{m: C.mapnik_identifier_new_uint64(C.ulonglong(v))}
	case int64:
		return &Identifier{m: C.mapnik_identifier_new_int64(C.longlong(v))}
	case float64:
		return &Identifier{m: C.mapnik_identifier_new_double(C.double(v))}
	case string:
		cstr := C.CString(v)
		defer C.free(unsafe.Pointer(cstr))
		return &Identifier{m: C.mapnik_identifier_new_string(cstr)}
	}
	return nil
}

func NewVaule(t interface{}) *Vaule {
	switch v := t.(type) {
	case bool:
		return &Vaule{m: C.mapnik_property_value_new_bool(C.bool(v))}
	case uint64:
		return &Vaule{m: C.mapnik_property_value_new_uint64(C.ulonglong(v))}
	case int64:
		return &Vaule{m: C.mapnik_property_value_new_int64(C.longlong(v))}
	case float64:
		return &Vaule{m: C.mapnik_property_value_new_double(C.double(v))}
	case string:
		cstr := C.CString(v)
		defer C.free(unsafe.Pointer(cstr))
		return &Vaule{m: C.mapnik_property_value_new_string(cstr)}
	}
	return &Vaule{m: C.mapnik_property_value_new()}
}

func (p *Property) SetVaule(key string, t interface{}) {
	keystr := C.CString(key)
	defer C.free(unsafe.Pointer(keystr))
	switch v := t.(type) {
	case bool:
		C.mapnik_property_map_set_bool(p.m, keystr, C.bool(v))
	case uint64:
		C.mapnik_property_map_set_uint64(p.m, keystr, C.ulonglong(v))
	case int64:
		C.mapnik_property_map_set_int64(p.m, keystr, C.longlong(v))
	case float64:
		C.mapnik_property_map_set_double(p.m, keystr, C.double(v))
	case string:
		cstr := C.CString(v)
		defer C.free(unsafe.Pointer(cstr))
		C.mapnik_property_map_set_string(p.m, keystr, cstr)
	}
	C.mapnik_property_map_set_null(p.m, keystr)
}
