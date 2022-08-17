cmake_minimum_required(VERSION 3.13)
project(disjoint_CBSH)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(library/yaml-cpp)

include_directories(.
        $ENV{GUROBI_HOME}/include
        library/yaml-cpp
        )

link_libraries(boost_program_options
        boost_graph
        pthread
        glog
        stdc++fs
        $ENV{GUROBI_HOME}/lib/libgurobi_c++.a
        $ENV{GUROBI_HOME}/lib/libgurobi95.so
        yaml-cpp
        )

add_executable(idcbs
        example/idcbs_adapter.cpp
#        driver.cpp
        agents_loader.cpp
        agents_loader.h
        common.cpp
        common.h
        heuristic_calculator.cpp
        heuristic_calculator.h
        dynamic_constraints_manager.cpp
        dynamic_constraints_manager.h
        g_logging.h
        ICBSNode.cpp
        ICBSNode.h
        ICBSSearch.cpp
        ICBSSearch.h
        ICBSSingleAgentLLNode.cpp
        ICBSSingleAgentLLNode.h
        lpa_node.cpp
        lpa_node.h
        lpa_star.cpp
        lpa_star.h
        map_loader.cpp
        map_loader.h
        MDD.cpp
        MDD.h
        ICBSSingleAgentLLSearch.cpp
        ICBSSingleAgentLLSearch.h
        conflict_avoidance_table.h
        conflict_avoidance_table.cpp
        XytHolder.cpp
        XytHolder.h)
