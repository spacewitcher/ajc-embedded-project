# Si la structure des modules change dans le projet changer MODULES en conséquence
MODULES 	:= app io misc model
# Permet d'inclure des librairie au linker ex -lsqlite3
LINK_LIB	:=
# Permet d'inclure des librairie au linker pour les tests ex -lsqlite3
TEST_LINK_LIB:=
ifeq ($(CROSS_COMPILE),1)
# remplacer le compilateur utilisé pour la cross-compilation ici
	CC	:= ../cross-pi-gcc-10.3.0-2/bin/arm-linux-gnueabihf-g++
# Nom de l'exécutable cross-compile
	EXEC		:= app-master
else 
	CC	:= g++
# Nom de l'exécutable
	EXEC		:= app
endif
# Extension à compiler
EXT			:= cpp
# Options de compilations
CFLAGS		:= -Wall
# Options de compilation pour le Debug
DEBUG_CFLAGS := -g
# Dossier racine des headers
INCLUDE_DIR := src/include
# Dossier racine des headers de tests
TEST_INCLUDE_DIR := src/test/include
# Dossier racine du code source
SOURCE_DIR	:= src/code
# Dossier racine du code de tests
TEST_SRC_DIR:= src/test
# Dossier de build
BUILD_DIR	:= build
# Dossier racine des fichiers .o
OBJ_DIR		:= obj
# Dossier debug
DEBUG_DIR	:= debug
# Dossier release
RELEASE_DIR	:= release
# Dossier test
TEST_DIR	:= test
# Ensemble des sous dossier obj/debug à créer par module
OBJ_DEBUG_DIR := $(foreach module, $(MODULES), $(DEBUG_DIR)/$(module))
# Ensemble des sous dossier obj/release à créer par module
OBJ_RELEASE_DIR := $(foreach module, $(MODULES), $(RELEASE_DIR)/$(module))
# Ensemble des sous dossier obj/test à créer par module
OBJ_TEST_DIR:= $(foreach module, $(MODULES), $(TEST_DIR)/$(module))
# Dossier build/debug
BUILD_DEBUG_DIR	:= $(BUILD_DIR)/$(DEBUG_DIR)
# Dossier build/release
BUILD_RELEASE_DIR := $(BUILD_DIR)/$(RELEASE_DIR)
# Dossier build/test
BUILD_TEST_DIR	:= $(BUILD_DIR)/$(TEST_DIR)
# Include config/debug
DEBUG_CONFIG_INCLUDE := -I./config/debug
# Include config/release
RELEASE_CONFIG_INCLUDE := -I./config/release

# Contient les dossier à inclure avec -I dans les commandes de compilation afin de simplifier l'écriture du code
INCLUDE		:= -I./$(INCLUDE_DIR)
INCLUDE	+= $(foreach module, $(MODULES), -I./$(INCLUDE_DIR)/$(module))

# Contient les dossiers à inclure
TEST_INCLUDE 	:= -I./$(TEST_INCLUDE_DIR)
TEST_INCLUDE	+= $(foreach module, $(MODULES), -I./$(TEST_INCLUDE_DIR)/$(module))

# Identifier tpous les fichiers .$(EXT)
SRC	:= $(wildcard $(SOURCE_DIR)/*.$(EXT))
SRC_MODULES	:= $(foreach module,$(MODULES),$(wildcard $(SOURCE_DIR)/$(module)/*.$(EXT)))
SRC	+= $(SRC_MODULES)

TEST_SRC	:= $(wildcard $(TEST_SRC_DIR)/*.$(EXT))
TEST_SRC	+= $(foreach module,$(MODULES),$(wildcard $(TEST_SRC_DIR)/$(module)/*.$(EXT)))

# Créer une liste des fichiers .o liés aux fichiers .$(EXT), pour le debug, une pour la version release
OBJ_DEBUG :=$(addprefix $(OBJ_DIR)/$(DEBUG_DIR)/,$(SRC:$(SOURCE_DIR)/%.$(EXT)=%.o))
OBJ_DEBUG_TEST :=$(addprefix $(OBJ_DIR)/$(DEBUG_DIR)/,$(SRC_MODULES:$(SOURCE_DIR)/%.$(EXT)=%.o))
OBJ_RELEASE :=$(addprefix $(OBJ_DIR)/$(RELEASE_DIR)/,$(SRC:$(SOURCE_DIR)/%.$(EXT)=%.o))
OBJ_TEST := $(addprefix $(OBJ_DIR)/$(TEST_DIR)/,$(TEST_SRC:$(TEST_SRC_DIR)/%.$(EXT)=%.o))


# Affiche le nom de la source qui doit être compilée
%.$(EXT):
	@echo compiling $(SOURCE_DIR)/$@

# Crée les sous dossiers obj/debug
$(DEBUG_DIR)/%:
	@mkdir -p $(OBJ_DIR)/$@

# Crée les sous dossiers obj/release
$(RELEASE_DIR)/%:
	@mkdir  -p $(OBJ_DIR)/$@

# Crée les sous dossiers obj/test
$(TEST_DIR)/%:
	@mkdir  -p $(OBJ_DIR)/$@

# Crée le dossier build/debug
$(BUILD_DEBUG_DIR):
	@mkdir -p $@

# Compile l'application debug mais également les sources si nécessaire
$(BUILD_DEBUG_DIR)/$(EXEC): $(OBJ_DEBUG)
	$(CC) $(INCLUDE) $(DEBUG_CONFIG_INCLUDE) -o $@ $(OBJ_DEBUG) $(CFLAGS) $(LINK_LIB)

# Crée le dossier build/release
$(BUILD_RELEASE_DIR):
	@mkdir -p $@

# Compile l'application release mais également les sources si nécessaire
$(BUILD_RELEASE_DIR)/$(EXEC): $(OBJ_RELEASE)
	$(CC) $(INCLUDE) $(RELEASE_CONFIG_INCLUDE) -o $@ $(OBJ_RELEASE) $(CFLAGS) $(LINK_LIB)

# Crée le dossier build/test
$(BUILD_TEST_DIR):
	@mkdir -p $@

# Compile l'application release mais également les sources si nécessaire
$(BUILD_TEST_DIR)/$(EXEC): $(OBJ_DEBUG_TEST) $(OBJ_TEST)
	$(CC) $(INCLUDE) $(DEBUG_CONFIG_INCLUDE) $(TEST_INCLUDE) -o $@ $(OBJ_DEBUG_TEST) $(OBJ_TEST) $(CFLAGS) $(DEBUG_CFLAGS) $(LINK_LIB) $(TEST_LINK_LIB)

# Compile les fichiers sources en mode debug
$(OBJ_DIR)/$(DEBUG_DIR)/%.o: $(SOURCE_DIR)/%.$(EXT)
	$(CC) $(INCLUDE) $(DEBUG_CONFIG_INCLUDE) -o $@ -c $< $(CFLAGS) $(LINK_LIB)

# Compile les fichiers sources en mode release
$(OBJ_DIR)/$(RELEASE_DIR)/%.o: $(SOURCE_DIR)/%.$(EXT)
	$(CC) $(INCLUDE) $(RELEASE_CONFIG_INCLUDE) -o $@ -c $< $(CFLAGS) $(LINK_LIB)

# Compile les fichiers sources de tests
$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_SRC_DIR)/%.$(EXT)
	$(CC) $(INCLUDE) $(DEBUG_CONFIG_INCLUDE) $(TEST_INCLUDE) -o $@ -c $< $(CFLAGS) $(DEBUG_CFLAGS) $(LINK_LIB) $(TEST_LINK_LIB)

# Lance la compilation en mode debug en changeant les flags de compilation
debug: CFLAGS := $(CFLAGS) $(DEBUG_CFLAGS)

# Les dossiers obj/debugs et build/debug sont créés, puis l'exécutable
debug: $(OBJ_DEBUG_DIR) $(BUILD_DEBUG_DIR) $(BUILD_DEBUG_DIR)/$(EXEC)
	@echo Debug make completed
	
# Lance la compilation en mode release en changeant les flags de compilations
release: CFLAGS := $(CFLAGS) -O2

# Les dossiers obj/debugs et build/debug sont créés, puis l'exécutable
release: $(OBJ_RELEASE_DIR) $(BUILD_RELEASE_DIR) $(BUILD_RELEASE_DIR)/$(EXEC)
	@echo Release make completed

# Les dossiers obj/debugs, obj/test et build/test sont créés, puis l'exécutable
test: $(OBJ_DEBUG_DIR) $(OBJ_TEST_DIR) $(BUILD_TEST_DIR) $(BUILD_TEST_DIR)/$(EXEC)
	@echo Test make completed

# Supprime le dossier obj
clean:
	@rm -rvf $(OBJ_DIR)

# Supprime le dossier build
mrproper: clean
	@rm -rvf $(BUILD_DIR)