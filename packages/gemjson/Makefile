include $(TOPDIR)/rules.mk
 
# Name, version and release number
# The name and version of your package are used to define the variable to point to the build directory of your package: $(PKG_BUILD_DIR)
PKG_NAME:=gemjson
PKG_VERSION:=1.0
PKG_RELEASE:=1
 
# Source settings (i.e. where to find the source codes)
# This is a custom variable, used below
SOURCE_DIR:=/home/chris/git/github.com/cpswan/OpenWrt-test-packages/packages/gemjson
 
include $(INCLUDE_DIR)/package.mk
 
# Package definition; instructs on how and where our package will appear in the overall configuration menu ('make menuconfig')
define Package/gemjson
  SECTION:=examples
  CATEGORY:=Examples
  TITLE:=Gemini test for cJSON
  DEPENDS:=+cJSON
endef
 
# Package description; a more verbose description on what our package does
define Package/helloworld/description
  Creates and parses some JSON
endef
 
# Package preparation instructions; create the build directory and copy the source code. 
# The last command is necessary to ensure our preparation instructions remain compatible with the patching system.
define Build/Prepare
		mkdir -p $(PKG_BUILD_DIR)
		cp $(SOURCE_DIR)/* $(PKG_BUILD_DIR)
		$(Build/Patch)
endef
 
# Package build instructions; invoke the target-specific compiler to first compile the source file, and then to link the file into the final executable
define Build/Compile
		$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/gemjson.o -c $(PKG_BUILD_DIR)/gemjson.c
		$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/cJSON.o -c $(PKG_BUILD_DIR)/cJSON.c
		$(TARGET_CC) $(TARGET_LDFLAGS) -o $(PKG_BUILD_DIR)/$1 $(PKG_BUILD_DIR)/gemjson.o $(PKG_BUILD_DIR)/cJSON.o
endef
 
# Package install instructions; create a directory inside the package to hold our executable, and then copy the executable we built previously into the folder
define Package/gemjson/install
		$(INSTALL_DIR) $(1)/usr/bin
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/gemjson $(1)/usr/bin
endef
 
# This command is always the last, it uses the definitions and variables we give above in order to get the job done
$(eval $(call BuildPackage,gemjson))
