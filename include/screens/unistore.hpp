#ifndef _UNIVERSAL_UPDATER_UNISTORE_HPP
#define _UNIVERSAL_UPDATER_UNISTORE_HPP

#include "common.hpp"
#include "fileBrowse.hpp"
#include "scriptHelper.hpp"
#include "structs.hpp"

#include <vector>

class UniStore : public Screen {
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	UniStore(bool doAutoboot, std::string file);
private:
	bool doAutoboot = false;
	std::string autobootFile = "";
	void refreshList();
	nlohmann::json openStoreFile();
	void loadStoreDesc(void);
	StoreInfo parseStoreInfo(std::string fileName);
	void autobootLogic();

	void DrawSubMenu(void) const;
	void DrawStoreList(void) const;
	void DrawSearch(void) const;
	void DrawFullURLScreen(void) const;
	void DrawGitHubScreen(void) const;

	void SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void StoreSelectionLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void SearchLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void FullURLLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void GitHubLogic(u32 hDown, u32 hHeld, touchPosition touch);

	void descript();
	void updateStore(int selectedStore);
	void deleteStore(int selectedStore);
	bool handleIfDisplayText();
	int mode = 0;
	bool displayInformations = true;

	// Stuff for the GitHub Store Search function and Full URL.
	std::string OwnerAndRepo = "";
	std::string fileName = "";
	std::string FullURL = "";

	// Selections.
	mutable int Selection = 0;
	int screenPos = 0;
	mutable int screenPosList = 0;
	bool dropDownMenu = false;
	int dropSelection = 0;

	// Browse stuff.
	int keyRepeatDelay = 0;
	std::vector<DirEntry> dirContents;

	// Other stuff.
	std::vector<StoreInfo> storeInfo; // Store Selection.
	std::vector<std::string> descLines;
	std::string storeDesc = "";
	nlohmann::json JSON;
	std::string currentStoreFile;

	// Icon | Button Structs.
	const std::vector<Structs::ButtonPos> arrowPos = {
		{295, 0, 25, 25}, // Arrow Up.
		{295, 215, 25, 25}, // Arrow Down.
		{0, 215, 25, 25}, // Back Arrow.
		{5, 0, 25, 25}  // Dropdown Menu.
	};

	const std::vector<Structs::ButtonPos> URLBtn = {
		{0, 60, 149, 52}, // FULL URL.
		{162, 60, 149, 52}, // GitHub.
		{0, 130, 149, 52}, // TinyDB.
		{162, 130, 149, 52} // Universal-DB.
	};

	const std::vector<Structs::ButtonPos> GitHubPos = {
		{30, 50, 260, 30}, // Owner & Repo.
		{30, 130, 260, 30}, // Filename.
		{135, 180, 50, 30} // OK.
	};

	const std::vector<Structs::ButtonPos> subPos = {
		{80, 60, 149, 52}, // StoreList.
		{80, 120, 149, 52}, // storeSearch.
	};

	// DropDownMenu.
	const std::vector<Structs::ButtonPos> dropPos = {
		{5, 30, 25, 25}, // Delete.
		{5, 70, 25, 25}, // Update.
		{5, 110, 25, 25} // ViewMode.
	};

	const std::vector<Structs::ButtonPos> dropPos2 = {
		{0, 28, 140, 30}, // Delete.
		{0, 68, 140, 30}, // Update.
		{0, 108, 140, 30} // ViewMode.
	};
};

#endif