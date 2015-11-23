##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=3dLocalisation
ConfigurationName      :=Debug
WorkspacePath          := "/home/rude/Desktop/Codelite"
ProjectPath            := "/home/rude/Desktop/Codelite/3dLocalisation"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=rude
Date                   :=21/11/15
CodeLitePath           :="/home/rude/.codelite"
LinkerName             :=/usr/bin/g++-4.9
SharedObjectLinkerName :=/usr/bin/g++-4.9 -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="3dLocalisation.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  `pkg-config --libs  opencv glew`
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/local/include/opencv $(IncludeSwitch)-I/usr/local/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)glut 
ArLibs                 :=  "glut" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++-4.9
CC       := /usr/bin/gcc-4.9
CXXFLAGS :=  -g -O0 -Wall  $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_shader.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_GLutil.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_voxelOperations.cpp$(ObjectSuffix) 



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
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	ln -sf ../src/shader.frag Debug/shader.frag
	ln -sf ../src/shader.vert Debug/shader.vert
	ln -sf ../src/bb.jpg Debug/bb.jpg
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_shader.cpp$(ObjectSuffix): src/shader.cpp $(IntermediateDirectory)/src_shader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Desktop/Codelite/3dLocalisation/src/shader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_shader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_shader.cpp$(DependSuffix): src/shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_shader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_shader.cpp$(DependSuffix) -MM "src/shader.cpp"

$(IntermediateDirectory)/src_shader.cpp$(PreprocessSuffix): src/shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_shader.cpp$(PreprocessSuffix) "src/shader.cpp"

$(IntermediateDirectory)/src_GLutil.cpp$(ObjectSuffix): src/GLutil.cpp $(IntermediateDirectory)/src_GLutil.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Desktop/Codelite/3dLocalisation/src/GLutil.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GLutil.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_GLutil.cpp$(DependSuffix): src/GLutil.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_GLutil.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_GLutil.cpp$(DependSuffix) -MM "src/GLutil.cpp"

$(IntermediateDirectory)/src_GLutil.cpp$(PreprocessSuffix): src/GLutil.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_GLutil.cpp$(PreprocessSuffix) "src/GLutil.cpp"

$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix): src/Main.cpp $(IntermediateDirectory)/src_Main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Desktop/Codelite/3dLocalisation/src/Main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Main.cpp$(DependSuffix): src/Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Main.cpp$(DependSuffix) -MM "src/Main.cpp"

$(IntermediateDirectory)/src_Main.cpp$(PreprocessSuffix): src/Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Main.cpp$(PreprocessSuffix) "src/Main.cpp"

$(IntermediateDirectory)/src_voxelOperations.cpp$(ObjectSuffix): src/voxelOperations.cpp $(IntermediateDirectory)/src_voxelOperations.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/rude/Desktop/Codelite/3dLocalisation/src/voxelOperations.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_voxelOperations.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_voxelOperations.cpp$(DependSuffix): src/voxelOperations.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_voxelOperations.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_voxelOperations.cpp$(DependSuffix) -MM "src/voxelOperations.cpp"

$(IntermediateDirectory)/src_voxelOperations.cpp$(PreprocessSuffix): src/voxelOperations.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_voxelOperations.cpp$(PreprocessSuffix) "src/voxelOperations.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


