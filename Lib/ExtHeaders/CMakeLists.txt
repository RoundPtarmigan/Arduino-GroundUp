add_library(ExtHeaders INTERFACE)

target_sources(ExtHeaders
  INTERFACE 
    FILE_SET HEADERS
    FILES 
      ioExtend.h
)