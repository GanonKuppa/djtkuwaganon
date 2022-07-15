# -----------------------------------------------------------------------------
# task runner makefile           ----------------------------------------------
# -----------------------------------------------------------------------------
MAKEFILE_DIR := $(dir $(abspath ($(lastword $(MAKEFILE_LIST)))))


.PHONY: pwd
pwd:
ifeq ($(OS),Windows_NT)
	echo $(MAKEFILE_DIR)
else
	echo $(MAKEFILE_DIR)
endif

.PHONY: help
help: ## makefileターゲット一覧表示
	@ echo ---- target list ----
ifeq ($(OS),Windows_NT)
	@findstr -r "[a-z][^\.PHONY][a-z]:" Makefile
else
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
endif

.PHONY: sim
sim: ## シミュレーター起動 (Windows環境用)
ifeq ($(OS),Windows_NT)
	@ cd tool/UMazeSim & npm run run
else
	@ echo This target is not supported under Linux.
endif

.PHONY: build
build: ## マイコン用motファイル生成	
ifeq ($(OS),Windows_NT)
	cmake -S src -B build -G Ninja -DCMAKE_MAKE_PROGRAM="C:/ninja-win/ninja"
	cmake --build build
else
	cmake -S src -B build -G Ninja
	cmake --build build
endif

.PHONY: build_act1
build_act1: ## djtkuwaganon_act1用motファイル生成	
ifeq ($(OS),Windows_NT)
	cmake -S src -B build -G Ninja -DCMAKE_MAKE_PROGRAM="C:/ninja-win/ninja" -DACT1=ON
	cmake --build build
else
	cmake -S src -B build -G Ninja -DACT1=ON
	cmake --build build
endif

.PHONY: build_act2
build_act2: ## djtkuwaganon_act2用motファイル生成	
ifeq ($(OS),Windows_NT)
	cmake -S src -B build -G Ninja -DCMAKE_MAKE_PROGRAM="C:/ninja-win/ninja" -DACT2=ON
	cmake --build build
else
	cmake -S src -B build -G Ninja -DACT2=ON
	cmake --build build
endif


.PHONY: clean
clean: ## buildディレクトリを消去
ifeq ($(OS),Windows_NT)
	cd $(MAKEFILE_DIR) & rmdir /s /q build > NUL 2>&1 & if ERRORLEVEL 1 cmd /c exit 0	
else
	cd $(MAKEFILE_DIR) ; rm -rf build
	cd $(MAKEFILE_DIR) ; find test -name *build | xargs rm -rf
endif
	@ echo cleaned

.PHONY: format
format: ## コード成形実行
ifeq ($(OS),Windows_NT)
	cd tool/astyle & code_format.bat
else
	cd tool/astyle; ./code_format.sh
endif

.PHONY: doxygen
doxygen: ## doxygen実行
ifeq ($(OS),Windows_NT)
	cd tool/doxygen & run_doxygen.bat
else
	@ echo This target is not supported under Linux.
endif

.PHONY: param_gen
doxygen: ## パラメータ定義からコードを自動生成
ifeq ($(OS),Windows_NT)
	@ echo hoge.
else
	@ echo hoge.
endif


.PHONY: test_simSearch
test_simSearch: ## 探索シミュレーション
ifeq ($(OS),Windows_NT)
	@ echo This target is not supported under Windows.
else
	- mkdir -p test/simSearch/build
	- cd test/simSearch/build; cmake .. -G Ninja                         
	- cd test/simSearch/build; ninja
	- test/simSearch/build/main
endif

.PHONY: test_simShortest
test_simShortest: ## 最短走行シミュレーション
ifeq ($(OS),Windows_NT)
	@ echo This target is not supported under Windows.
else
	- mkdir -p test/simShortest/build
	- cd test/simShortest/build; cmake .. -G Ninja                         
	- cd test/simShortest/build; ninja
	- test/simShortest/build/main
endif

.PHONY: test_traj
test_traj: ## ターン軌跡自動生成前後距離表示テスト
ifeq ($(OS),Windows_NT)
	@ echo This target is not supported under Windows.
else
	- mkdir -p test/traj/build
	- cd test/traj/build; cmake .. -G Ninja                         
	- cd test/traj/build; ninja
	- test/traj/build/main
endif

.PHONY: test_trajSetpoint
test_trajSetpoint: ## ターンセットポイントcsv出力テスト
ifeq ($(OS),Windows_NT)
	@ echo This target is not supported under Windows.
else
	- mkdir -p test/trajSetpoint/build
	- cd test/trajSetpoint/build; cmake .. -G Ninja                         
	- cd test/trajSetpoint/build; ninja
	- test/trajSetpoint/build/main
endif