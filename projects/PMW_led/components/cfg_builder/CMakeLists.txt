idf_component_register(
                    SRCS "timer_cfg.c" "channel_cfg.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_ledc
                    )
