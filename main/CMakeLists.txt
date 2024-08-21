set(SOURCES
    webserver/webserver.c
    gy_21/gy_21.c
    main.c
)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS "." "../include")