package mapnik

import (
	"fmt"
	"io/ioutil"
	"os"
	"testing"
)

func TestMapnikTiler(t *testing.T) {
	m := New()
	if err := m.Load("test/map.xml"); err != nil {
		t.Fatal(err)
	}
	m.ZoomAll()

	out, err := ioutil.TempDir("", "")
	if err != nil {
		t.Fatal("unable to create temp dir")
	}
	defer os.RemoveAll(out)

	mp := make(map[string]Map)
	mp["test"] = *m
	tlsource := NewTilerSource(mp)
	layers := []string{"layerA", "layerB", "layerC", "layeD"}
	grid := NewGlobalMercatorGrid(256)
	tl := NewTiler("test", layers, tlsource, grid)
	fun := func(tl *Tile) {
		fmt.Println(tl.Count())
		tl.Free()
	}
	tl.Render(3, 2, fun)
}

func TestMvtTiler(t *testing.T) {
	m := New()
	if err := m.Load("test/map.xml"); err != nil {
		t.Fatal(err)
	}
	m.ZoomAll()

	out, err := ioutil.TempDir("", "")
	if err != nil {
		t.Fatal("unable to create temp dir")
	}
	defer os.RemoveAll(out)

	mp := make(map[string]Map)
	mp["test"] = *m
	tlsource := NewTilerSource(mp)
	layers := []string{"layerA", "layerB", "layerC", "layeD"}
	grid := NewGlobalMercatorGrid(256)
	tl := NewMvtTiler("test", layers, tlsource, grid)
	fun := func(tl *MvtTile) {
		fmt.Println(tl.Count())
		tl.Free()
	}
	tl.Render(2, 1, fun)
}

func TestUtfgridTiler(t *testing.T) {
	m := New()
	if err := m.Load("test/map.xml"); err != nil {
		t.Fatal(err)
	}
	m.ZoomAll()

	out, err := ioutil.TempDir("", "")
	if err != nil {
		t.Fatal("unable to create temp dir")
	}
	defer os.RemoveAll(out)

	mp := make(map[string]Map)
	mp["test"] = *m
	tlsource := NewTilerSource(mp)
	layers := []string{"layerA", "layerB", "layerC", "layeD"}
	grid := NewGlobalMercatorGrid(256)
	tl := NewUtfgridTiler("test", layers, tlsource, grid)
	fun := func(tl *UtfgridTile) {
		fmt.Println(tl.Count())
		tl.Free()
	}
	tl.Render(3, 2, fun)
}
