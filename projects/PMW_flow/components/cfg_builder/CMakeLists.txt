idf_component_register(
                    SRCS "timer_cfg.c" "channel_manager.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_ledc
                    )
