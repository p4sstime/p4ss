block()
include(cmake/source_lib_base.cmake)

add_library(tier1 STATIC)
set_target_properties(tier1 PROPERTIES PREFIX "")
target_compile_definitions(tier1 PRIVATE
TIER1_STATIC_LIB
)

if(${IS_WINDOWS})
	target_link_libraries(tier1 PRIVATE "Rpcrt4.lib")
endif()

set(SOURCE_LIST
${SRCDIR}/tier1/bitbuf.cpp
${SRCDIR}/tier1/newbitbuf.cpp
${SRCDIR}/tier1/byteswap.cpp
${SRCDIR}/tier1/characterset.cpp
${SRCDIR}/tier1/checksum_crc.cpp
${SRCDIR}/tier1/checksum_md5.cpp
${SRCDIR}/tier1/checksum_sha1.cpp
${SRCDIR}/tier1/commandbuffer.cpp
${SRCDIR}/tier1/convar.cpp
${SRCDIR}/tier1/datamanager.cpp
${SRCDIR}/tier1/diff.cpp
${SRCDIR}/tier1/exprevaluator.cpp
${SRCDIR}/tier1/generichash.cpp
${SRCDIR}/tier1/ilocalize.cpp
${SRCDIR}/tier1/interface.cpp
${SRCDIR}/tier1/KeyValues.cpp
${SRCDIR}/tier1/keyvaluesjson.cpp
${SRCDIR}/tier1/kvpacker.cpp
${SRCDIR}/tier1/lzmaDecoder.cpp
# ${SRCDIR}/tier1/lzss.cpp" [!$SOURCESDK]
${SRCDIR}/tier1/mempool.cpp
${SRCDIR}/tier1/memstack.cpp
${SRCDIR}/tier1/NetAdr.cpp
${SRCDIR}/tier1/splitstring.cpp
${SRCDIR}/tier1/rangecheckedvar.cpp
${SRCDIR}/tier1/reliabletimer.cpp
${SRCDIR}/tier1/stringpool.cpp
${SRCDIR}/tier1/strtools.cpp
${SRCDIR}/tier1/strtools_unicode.cpp
${SRCDIR}/tier1/tier1.cpp
${SRCDIR}/tier1/tokenreader.cpp
${SRCDIR}/tier1/sparsematrix.cpp
${SRCDIR}/tier1/uniqueid.cpp
${SRCDIR}/tier1/utlbuffer.cpp
${SRCDIR}/tier1/utlbufferutil.cpp
${SRCDIR}/tier1/utlstring.cpp
${SRCDIR}/tier1/utlsymbol.cpp
${SRCDIR}/tier1/utlbinaryblock.cpp
${SRCDIR}/tier1/snappy.cpp
${SRCDIR}/tier1/snappy-sinksource.cpp
${SRCDIR}/tier1/snappy-stubs-internal.cpp
)

if(${IS_WINDOWS})
	# Add this Windows exclusive file
	set(SOURCE_LIST "${SOURCE_LIST} ${SRCDIR}/tier1/processor_detect.cpp")
	# And enable C++ exceptions for it?
	set_source_files_properties("${SRCDIR}/tier1/processor_detect.cpp" PROPERTIES COMPILE_FLAGS "/EHsc")
elseif(${IS_LINUX})
	# Add these Linux exclusive files
	set(SOURCE_LIST ${SOURCE_LIST} 
	${SRCDIR}/tier1/processor_detect_linux.cpp
	${SRCDIR}/tier1/qsort_s.cpp
	${SRCDIR}/tier1/pathmatch.cpp
	)
endif()

set(SOURCE_LIST_LZMA_SUPPORT
		${SRCDIR}/utils/lzma/C/LzmaDec.h
		${SRCDIR}/utils/lzma/C/LzmaDec.c
		${SRCDIR}/utils/lzma/C/7zTypes.h
)

set(HEADER_LIST
${SRCDIR}/public/tier1/bitbuf.h
${SRCDIR}/public/tier1/byteswap.h
${SRCDIR}/public/tier1/callqueue.h
${SRCDIR}/public/tier1/characterset.h
${SRCDIR}/public/tier1/checksum_crc.h
${SRCDIR}/public/tier1/checksum_md5.h
${SRCDIR}/public/tier1/checksum_sha1.h
${SRCDIR}/public/tier1/CommandBuffer.h
${SRCDIR}/public/tier1/convar.h
${SRCDIR}/public/tier1/datamanager.h
${SRCDIR}/public/datamap.h
${SRCDIR}/public/tier1/delegates.h
${SRCDIR}/public/tier1/diff.h
${SRCDIR}/public/tier1/fmtstr.h
${SRCDIR}/public/tier1/functors.h
${SRCDIR}/public/tier1/generichash.h
${SRCDIR}/public/tier1/iconvar.h
${SRCDIR}/public/tier1/ilocalize.h
${SRCDIR}/public/tier1/interface.h
${SRCDIR}/public/tier1/KeyValues.h
${SRCDIR}/public/tier1/keyvaluesjson.h
${SRCDIR}/public/tier1/kvpacker.h
${SRCDIR}/public/tier1/lzmaDecoder.h
${SRCDIR}/public/tier1/lzss.h
${SRCDIR}/public/tier1/mempool.h
${SRCDIR}/public/tier1/memstack.h
${SRCDIR}/public/tier1/netadr.h
${SRCDIR}/public/tier1/processor_detect.h
${SRCDIR}/public/tier1/rangecheckedvar.h
${SRCDIR}/public/tier1/refcount.h
${SRCDIR}/public/tier1/smartptr.h
${SRCDIR}/public/tier1/snappy.h
${SRCDIR}/public/tier1/snappy-sinksource.h
${SRCDIR}/public/tier1/stringpool.h
${SRCDIR}/public/tier1/strtools.h
${SRCDIR}/public/tier1/tier1.h
${SRCDIR}/public/tier1/tokenreader.h
${SRCDIR}/public/tier1/util_misc.h
${SRCDIR}/public/tier1/utlbidirectionalset.h
${SRCDIR}/public/tier1/utlblockmemory.h
${SRCDIR}/public/tier1/utlbuffer.h
${SRCDIR}/public/tier1/utlbufferutil.h
${SRCDIR}/public/tier1/utlcommon.h
${SRCDIR}/public/tier1/utldict.h
${SRCDIR}/public/tier1/utlenvelope.h
${SRCDIR}/public/tier1/utlfixedmemory.h
${SRCDIR}/public/tier1/utlhandletable.h
${SRCDIR}/public/tier1/utlhash.h
${SRCDIR}/public/tier1/utlhashtable.h
${SRCDIR}/public/tier1/utllinkedlist.h
${SRCDIR}/public/tier1/utlmap.h
${SRCDIR}/public/tier1/utlmemory.h
${SRCDIR}/public/tier1/utlmultilist.h
${SRCDIR}/public/tier1/utlpriorityqueue.h
${SRCDIR}/public/tier1/utlqueue.h
${SRCDIR}/public/tier1/utlrbtree.h
${SRCDIR}/public/tier1/UtlSortVector.h
${SRCDIR}/public/tier1/utlstack.h
${SRCDIR}/public/tier1/utlstring.h
${SRCDIR}/public/tier1/UtlStringMap.h
${SRCDIR}/public/tier1/utlsymbol.h
${SRCDIR}/public/tier1/utlsymbollarge.h
${SRCDIR}/public/tier1/utlvector.h
${SRCDIR}/public/tier1/utlrange.h
${SRCDIR}/public/tier1/utlbinaryblock.h
${SRCDIR}/common/xbox/xboxstubs.h
)
set(INTERNAL_HEADER_LIST
${SRCDIR}/tier1/snappy-internal.h
${SRCDIR}/tier1/snappy-stubs-internal.h
)

if(${IS_WINDOWS})
set(HEADER_LIST 
${HEADER_LIST}
${SRCDIR}/public/tier1/uniqueid.h
)
endif()

target_sources(tier1 PRIVATE ${SOURCE_LIST})
source_group("C++ Source" FILES ${SOURCE_LIST})

target_sources(tier1 PRIVATE ${HEADER_LIST})
source_group("Public Header Files" FILES ${HEADER_LIST})

target_sources(tier1 PRIVATE ${INTERNAL_HEADER_LIST})
source_group("Public Header Files/Internal Header Files" FILES ${INTERNAL_HEADER_LIST})
endblock()