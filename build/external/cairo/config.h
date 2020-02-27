/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* whether memory barriers are needed around atomic operations */
/* #undef ATOMIC_OP_NEEDS_MEMORY_BARRIER */

/* Define to 1 if the PDF backend can be tested (need poppler and other
   dependencies for pdf2png) */
/* #undef CAIRO_CAN_TEST_PDF_SURFACE */

/* Define to 1 if the PS backend can be tested (needs ghostscript) */
/* #undef CAIRO_CAN_TEST_PS_SURFACE */

/* Define to 1 if the SVG backend can be tested */
/* #undef CAIRO_CAN_TEST_SVG_SURFACE */

/* Define to 1 if the Win32 Printing backend can be tested (needs ghostscript)
   */
/* #undef CAIRO_CAN_TEST_WIN32_PRINTING_SURFACE */

/* Define to 1 if dlsym is available */
/* #undef CAIRO_HAS_DLSYM */

/* Define to 1 to enable cairo's cairo-script-interpreter feature */
/* #undef CAIRO_HAS_INTERPRETER */

/* Define to 1 to enable cairo's pthread feature */
/* #undef CAIRO_HAS_PTHREAD */

/* Define to 1 if we have full pthread support */
/* #undef CAIRO_HAS_REAL_PTHREAD */

/* Define to 1 if libspectre is available */
/* #undef CAIRO_HAS_SPECTRE */

/* Define to 1 to enable cairo's symbol-lookup feature */
/* #undef CAIRO_HAS_SYMBOL_LOOKUP */

/* Define to 1 to enable cairo's test surfaces feature */
/* #undef CAIRO_HAS_TEST_SURFACES */

/* Define to 1 to enable cairo's cairo-trace feature */
/* #undef CAIRO_HAS_TRACE */

/* Define to 1 to disable certain code paths that rely heavily on
 double
   precision floating-point calculation */
/* #undef DISABLE_SOME_FLOATING_POINT */

/* Define to 1 if your system stores words within floats
 with the most
   significant word first */
/* #undef FLOAT_WORDS_BIGENDIAN */

/* Enable pixman glyph cache */
/* #undef HAS_PIXMAN_GLYPHS */

/* Define to 1 if you have the `alarm' function. */
#define HAVE_ALARM 1

/* Define to 1 if you have the binutils development files installed */
/* #undef HAVE_BFD */

/* Define to 1 if your compiler supports the __builtin_return_address()
   intrinsic. */
/* #undef HAVE_BUILTIN_RETURN_ADDRESS */

/* Define to 1 if you have the <byteswap.h> header file. */
#define HAVE_BYTESWAP_H 1

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define to 1 if you have the `ctime_r' function. */
#define HAVE_CTIME_R 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `drand48' function. */
#define HAVE_DRAND48 1

/* Define to 1 if you have the `FcFini' function. */
/* #undef HAVE_FCFINI */

/* Define to 1 if you have the `FcInit' function. */
/* #undef HAVE_FCINIT */

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `feclearexcept' function. */
/* #undef HAVE_FECLEAREXCEPT */

/* Define to 1 if you have the `fedisableexcept' function. */
/* #undef HAVE_FEDISABLEEXCEPT */

/* Define to 1 if you have the `feenableexcept' function. */
/* #undef HAVE_FEENABLEEXCEPT */

/* Define to 1 if you have the <fenv.h> header file. */
#define HAVE_FENV_H 1

/* Define to 1 if you have the `flockfile' function. */
#define HAVE_FLOCKFILE 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if you have the `FT_Get_X11_Font_Format' function. */
/* #undef HAVE_FT_GET_X11_FONT_FORMAT */

/* Define to 1 if you have the `FT_GlyphSlot_Embolden' function. */
/* #undef HAVE_FT_GLYPHSLOT_EMBOLDEN */

/* Define to 1 if you have the `FT_GlyphSlot_Oblique' function. */
/* #undef HAVE_FT_GLYPHSLOT_OBLIQUE */

/* Define to 1 if you have the `FT_Library_SetLcdFilter' function. */
/* #undef HAVE_FT_LIBRARY_SETLCDFILTER */

/* Define to 1 if you have the `FT_Load_Sfnt_Table' function. */
/* #undef HAVE_FT_LOAD_SFNT_TABLE */

/* Define to 1 if you have the `funlockfile' function. */
#define HAVE_FUNLOCKFILE 1

/* Whether you have gcov */
/* #undef HAVE_GCOV */

/* Define to 1 if you have the `getline' function. */
#define HAVE_GETLINE 1

/* Enable if your compiler supports the Intel __sync_* atomic primitives */
#define HAVE_INTEL_ATOMIC_PRIMITIVES 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <io.h> header file. */
/* #undef HAVE_IO_H */

/* Define to 1 if you have the <libgen.h> header file. */
#define HAVE_LIBGEN_H 1

/* Define to 1 if you have the `rt' library (-lrt). */
/* #undef HAVE_LIBRT */

/* Enable if you have libatomic-ops-dev installed */
/* #undef HAVE_LIB_ATOMIC_OPS */

/* Define to 1 if you have the `link' function. */
#define HAVE_LINK 1

/* Define to 1 if you have the Valgrind lockdep tool */
/* #undef HAVE_LOCKDEP */

/* Define to 1 if you have lzo available */
/* #undef HAVE_LZO */

/* Define to 1 if you have the Valgrind memfault tool */
/* #undef HAVE_MEMFAULT */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to non-zero if your system has mkdir, and to 2 if your version of
   mkdir requires a mode parameter */
#define HAVE_MKDIR 1

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Enable if you have MacOS X atomic operations */
/* #undef HAVE_OS_ATOMIC_OPS */

/* Define to 1 if you have the `poppler_page_render' function. */
/* #undef HAVE_POPPLER_PAGE_RENDER */

/* Define to 1 if you have the `raise' function. */
#define HAVE_RAISE 1

/* Define to 1 if you have the `rsvg_pixbuf_from_file' function. */
/* #undef HAVE_RSVG_PIXBUF_FROM_FILE */

/* Define to 1 if you have the `sched_getaffinity' function. */
#define HAVE_SCHED_GETAFFINITY 1

/* Define to 1 if you have the <sched.h> header file. */
#define HAVE_SCHED_H 1

/* Define to 1 if you have the <setjmp.h> header file. */
#define HAVE_SETJMP_H 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define to 1 if you have the <sys/int_types.h> header file. */
/* #undef HAVE_SYS_INT_TYPES_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/poll.h> header file. */
#define HAVE_SYS_POLL_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if the system has the type `uint128_t'. */
/* #undef HAVE_UINT128_T */

/* Define to 1 if the system has the type `uint64_t'. */
#define HAVE_UINT64_T 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have Valgrind */
/* #undef HAVE_VALGRIND */

/* Define to 1 if you have the `waitpid' function. */
#define HAVE_WAITPID 1

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define to 1 if you have the <X11/extensions/shmproto.h> header file. */
/* #undef HAVE_X11_EXTENSIONS_SHMPROTO_H */

/* Define to 1 if you have the <X11/extensions/shmstr.h> header file. */
/* #undef HAVE_X11_EXTENSIONS_SHMSTR_H */

/* Define to 1 if you have the <X11/extensions/XShm.h> header file. */
/* #undef HAVE_X11_EXTENSIONS_XSHM_H */

/* Define to 1 if you have the `XRenderCreateConicalGradient' function. */
/* #undef HAVE_XRENDERCREATECONICALGRADIENT */

/* Define to 1 if you have the `XRenderCreateLinearGradient' function. */
/* #undef HAVE_XRENDERCREATELINEARGRADIENT */

/* Define to 1 if you have the `XRenderCreateRadialGradient' function. */
/* #undef HAVE_XRENDERCREATERADIALGRADIENT */

/* Define to 1 if you have the `XRenderCreateSolidFill' function. */
/* #undef HAVE_XRENDERCREATESOLIDFILL */

/* Define to 1 if you have zlib available */
/* #undef HAVE_ZLIB */

/* Define to 1 if the system has the type `__uint128_t'. */
#define HAVE___UINT128_T 1

/* Define to 1 if shared memory segments are released deferred. */
/* #undef IPC_RMID_DEFERRED_RELEASE */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
/* #undef LT_OBJDIR */

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Define to the address where bug reports for this package should be sent. */
/* #undef PACKAGE_BUGREPORT */

/* Define to the full name of this package. */
/* #undef PACKAGE_NAME */

/* Define to the full name and version of this package. */
/* #undef PACKAGE_STRING */

/* Define to the one symbol short name of this package. */
/* #undef PACKAGE_TARNAME */

/* Define to the home page for this package. */
/* #undef PACKAGE_URL */

/* Define to the version of this package. */
/* #undef PACKAGE_VERSION */

/* Shared library file extension */
/* #undef SHARED_LIB_EXT */

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 8

/* The size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* The size of `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T 8

/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 8

/* Define to 1 if you have the ANSI C header files. */
/* #undef STDC_HEADERS */
