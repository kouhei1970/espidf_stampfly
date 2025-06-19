idf_component_register(SRCS 
                    "main.cpp"
                    "stampfly.cpp"
                    "task_scheduler.cpp"
                    "motor.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES sensors driver)
