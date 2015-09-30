##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=3dLocalisation
ConfigurationName      :=Debug
WorkspacePath          := "/home/spike/Workspace/Codelite"
ProjectPath            := "/home/spike/Workspace/Codelite/3dLocalisation"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=spike
Date                   :=30/09/15
CodeLitePath           :="/home/spike/.codelite"
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
LinkOptions            :=  `pkg-config --libs  opencv`
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/local/include/opencv $(IncludeSwitch)-I/usr/local/include 
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
Objects0=$(IntermediateDirectory)/src_3ddepthmap.cpp$(ObjectSuffix) 



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

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_3ddepthmap.cpp$(ObjectSuffix): src/3ddepthmap.cpp $(IntermediateDirectory)/src_3ddepthmap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/spike/Workspace/Codelite/3dLocalisation/src/3ddepthmap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_3ddepthmap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_3ddepthmap.cpp$(DependSuffix): src/3ddepthmap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_3ddepthmap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_3ddepthmap.cpp$(DependSuffix) -MM "src/3ddepthmap.cpp"

$(IntermediateDirectory)/src_3ddepthmap.cpp$(PreprocessSuffix): src/3ddepthmap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_3ddepthmap.cpp$(PreprocessSuffix) "src/3ddepthmap.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


