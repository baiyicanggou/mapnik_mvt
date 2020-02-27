.PHONY: test build

export CGO_LDFLAGS = $(shell mapnik-config --libs) -licuuc -lboost_system -lboost_thread
export CGO_CXXFLAGS = $(shell mapnik-config --cxxflags --includes --dep-includes | tr '\n' ' ')

MAPNIK_LDFLAGS=-X github.com/flywave/flywave-mapnik.fontPath=$(shell mapnik-config --fonts) \
	-X github.com/flywave/flywave-mapnik.pluginPath=$(shell mapnik-config --input-plugins)

build:
	go build -ldflags "$(MAPNIK_LDFLAGS)"

test:
	go test -ldflags "$(MAPNIK_LDFLAGS)"
