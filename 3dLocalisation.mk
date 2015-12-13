##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=3dLocalisation
ConfigurationName      :=Debug
WorkspacePath          := "/home/rude/Documents/NewWorkspace"
ProjectPath            := "/home/rude/Documents/NewWorkspace/3dLocalisation"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=rude
Date                   :=13/12/15
CodeLitePath           :="/home/rude/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="3dLocalisation.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_shader.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glad.c$(ObjectSuffix) $(IntermediateDirectory)/src_3ddepthmap.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_voxelOperations.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GLutil.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_3dlocalisation.cpp$(ObjectSuffix) $(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(ObjectSuffix) $(IntermediateDirectory)/FunctionTests_shadertest.cpp$(ObjectSuffix) $(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(ObjectSuffix) $(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(ObjectSuffix) $(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "/home/rude/Documents/NewWorkspace/.build-debug"
	@echo rebuilt > "/home/rude/Documents/NewWorkspace/.build-debug/3dLocalisation"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_shader.cpp$(ObjectSuffix): src/shader.cpp $(IntermediateDirectory)/src_shader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/shader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_shader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_shader.cpp$(DependSuffix): src/shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_shader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_shader.cpp$(DependSuffix) -MM "src/shader.cpp"

$(IntermediateDirectory)/src_shader.cpp$(PreprocessSuffix): src/shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_shader.cpp$(PreprocessSuffix) "src/shader.cpp"

$(IntermediateDirectory)/src_glad.c$(ObjectSuffix): src/glad.c $(IntermediateDirectory)/src_glad.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/glad.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_glad.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_glad.c$(DependSuffix): src/glad.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_glad.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_glad.c$(DependSuffix) -MM "src/glad.c"

$(IntermediateDirectory)/src_glad.c$(PreprocessSuffix): src/glad.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_glad.c$(PreprocessSuffix) "src/glad.c"

$(IntermediateDirectory)/src_3ddepthmap.cpp$(ObjectSuffix): src/3ddepthmap.cpp $(IntermediateDirectory)/src_3ddepthmap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/3ddepthmap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_3ddepthmap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_3ddepthmap.cpp$(DependSuffix): src/3ddepthmap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_3ddepthmap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_3ddepthmap.cpp$(DependSuffix) -MM "src/3ddepthmap.cpp"

$(IntermediateDirectory)/src_3ddepthmap.cpp$(PreprocessSuffix): src/3ddepthmap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_3ddepthmap.cpp$(PreprocessSuffix) "src/3ddepthmap.cpp"

$(IntermediateDirectory)/src_voxelOperations.cpp$(ObjectSuffix): src/voxelOperations.cpp $(IntermediateDirectory)/src_voxelOperations.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/voxelOperations.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_voxelOperations.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_voxelOperations.cpp$(DependSuffix): src/voxelOperations.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_voxelOperations.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_voxelOperations.cpp$(DependSuffix) -MM "src/voxelOperations.cpp"

$(IntermediateDirectory)/src_voxelOperations.cpp$(PreprocessSuffix): src/voxelOperations.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_voxelOperations.cpp$(PreprocessSuffix) "src/voxelOperations.cpp"

$(IntermediateDirectory)/src_GLutil.cpp$(ObjectSuffix): src/GLutil.cpp $(IntermediateDirectory)/src_GLutil.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/GLutil.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GLutil.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GLutil.cpp$(DependSuffix): src/GLutil.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GLutil.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GLutil.cpp$(DependSuffix) -MM "src/GLutil.cpp"

$(IntermediateDirectory)/src_GLutil.cpp$(PreprocessSuffix): src/GLutil.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GLutil.cpp$(PreprocessSuffix) "src/GLutil.cpp"

$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix): src/Main.cpp $(IntermediateDirectory)/src_Main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/Main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Main.cpp$(DependSuffix): src/Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Main.cpp$(DependSuffix) -MM "src/Main.cpp"

$(IntermediateDirectory)/src_Main.cpp$(PreprocessSuffix): src/Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Main.cpp$(PreprocessSuffix) "src/Main.cpp"

$(IntermediateDirectory)/src_3dlocalisation.cpp$(ObjectSuffix): src/3dlocalisation.cpp $(IntermediateDirectory)/src_3dlocalisation.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/3dlocalisation.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_3dlocalisation.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_3dlocalisation.cpp$(DependSuffix): src/3dlocalisation.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_3dlocalisation.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_3dlocalisation.cpp$(DependSuffix) -MM "src/3dlocalisation.cpp"

$(IntermediateDirectory)/src_3dlocalisation.cpp$(PreprocessSuffix): src/3dlocalisation.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_3dlocalisation.cpp$(PreprocessSuffix) "src/3dlocalisation.cpp"

$(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(ObjectSuffix): src/FunctionTests/mouseMove.cpp $(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/FunctionTests/mouseMove.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(DependSuffix): src/FunctionTests/mouseMove.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(DependSuffix) -MM "src/FunctionTests/mouseMove.cpp"

$(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(PreprocessSuffix): src/FunctionTests/mouseMove.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FunctionTests_mouseMove.cpp$(PreprocessSuffix) "src/FunctionTests/mouseMove.cpp"

$(IntermediateDirectory)/FunctionTests_shadertest.cpp$(ObjectSuffix): src/FunctionTests/shadertest.cpp $(IntermediateDirectory)/FunctionTests_shadertest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/FunctionTests/shadertest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FunctionTests_shadertest.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FunctionTests_shadertest.cpp$(DependSuffix): src/FunctionTests/shadertest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FunctionTests_shadertest.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FunctionTests_shadertest.cpp$(DependSuffix) -MM "src/FunctionTests/shadertest.cpp"

$(IntermediateDirectory)/FunctionTests_shadertest.cpp$(PreprocessSuffix): src/FunctionTests/shadertest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FunctionTests_shadertest.cpp$(PreprocessSuffix) "src/FunctionTests/shadertest.cpp"

$(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(ObjectSuffix): src/FunctionTests/geometryShaderTest.cpp $(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/FunctionTests/geometryShaderTest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(DependSuffix): src/FunctionTests/geometryShaderTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(DependSuffix) -MM "src/FunctionTests/geometryShaderTest.cpp"

$(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(PreprocessSuffix): src/FunctionTests/geometryShaderTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FunctionTests_geometryShaderTest.cpp$(PreprocessSuffix) "src/FunctionTests/geometryShaderTest.cpp"

$(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(ObjectSuffix): src/FunctionTests/modernshadertest.cpp $(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/FunctionTests/modernshadertest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(DependSuffix): src/FunctionTests/modernshadertest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(DependSuffix) -MM "src/FunctionTests/modernshadertest.cpp"

$(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(PreprocessSuffix): src/FunctionTests/modernshadertest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FunctionTests_modernshadertest.cpp$(PreprocessSuffix) "src/FunctionTests/modernshadertest.cpp"

$(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(ObjectSuffix): src/FunctionTests/marchingCubesTest.cpp $(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/FunctionTests/marchingCubesTest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(DependSuffix): src/FunctionTests/marchingCubesTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(DependSuffix) -MM "src/FunctionTests/marchingCubesTest.cpp"

$(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(PreprocessSuffix): src/FunctionTests/marchingCubesTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FunctionTests_marchingCubesTest.cpp$(PreprocessSuffix) "src/FunctionTests/marchingCubesTest.cpp"

$(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(ObjectSuffix): src/FunctionTests/3dtextureTest.cpp $(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Documents/NewWorkspace/3dLocalisation/src/FunctionTests/3dtextureTest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(DependSuffix): src/FunctionTests/3dtextureTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(DependSuffix) -MM "src/FunctionTests/3dtextureTest.cpp"

$(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(PreprocessSuffix): src/FunctionTests/3dtextureTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FunctionTests_3dtextureTest.cpp$(PreprocessSuffix) "src/FunctionTests/3dtextureTest.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


