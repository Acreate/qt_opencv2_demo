CMAKE_MINIMUM_REQUIRED( VERSION 3.5 )

SET( CMAKE_C_STANDARD 99 )
SET( CMAKE_C_STANDARD_REQUIRED ON )
SET( CMAKE_C_VISIBILITY_PRESET hidden )

SET( CMAKE_CXX_STANDARD 17 )
SET( CMAKE_CXX_STANDARD_REQUIRED ON )
SET( CMAKE_CXX_VISIBILITY_PRESET hidden )

INCLUDE( GenerateExportHeader )
INCLUDE( GNUInstallDirs )

### 根据目录获取一个文件夹名称
function(get_current_dir_name out_name in_path)
	STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${in_path} )
	set(${out_name} ${CURRENT_FOLDER} PARENT_SCOPE)
endfunction()

### 在目录中查找目录，并且在目标目录中找到 file_name 的文件名
### 若存在，则返回所在目录的路径
### 文件名不区分大小写
function(get_current_path_dirs out_list check_path_dir file_name)
	set(for_each_list_dirs ${${out_list}})
	string(TOUPPER ${file_name} file_name )
	if(IS_DIRECTORY ${check_path_dir} )
		FILE(GLOB child_dir RELATIVE ${check_path_dir} ${check_path_dir}/*)
		foreach(dir_path ${child_dir})
			set(current_path ${check_path_dir}/${dir_path})
			if(IS_DIRECTORY ${current_path})
				FILE(GLOB child_dir_in_files RELATIVE ${current_path} ${current_path}/*)
				foreach(current_path_file ${child_dir_in_files})
					string(TOUPPER ${current_path_file} current_path_file)
					if(IS_DIRECTORY ${check_path_dir}/${current_path_file})
					elseif(current_path_file STREQUAL ${file_name})
						list(APPEND for_each_list_dirs ${current_path} )
					endif()
				endforeach()
			endif()
		endforeach()
		set(${out_list} ${for_each_list_dirs} PARENT_SCOPE)
	endif( )
endfunction()

