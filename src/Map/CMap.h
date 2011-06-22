#ifndef __CMAP_H__
#define __CMAP_H__

#include <vector>
#include "CMapBase.h"
#include "../ResourceManager/IResource.h"
#include <SFML/Graphics/Rect.hpp>

class CPhysicalTemplate;

#ifdef __EDITOR__
#   ifdef PLATFORM_LINUX    // bo pod windowsem warning: macro M_PI redefinition
#       include "src/CEditorWnd.h"
#       include "../Editor/CTileResource.h"
#   else
        class CTileResource;
        class CEditorWnd;
#   endif
#endif

namespace Map{
    class CTile;
    class CMapObjectDescriptor;
	class CDoodahDescriptor;
	class CRegionDescriptor;
    // definiowane w CMap.cpp:
    class CMapTileType;
	class CMapObjectType;

	const int TILE_SIZE = 64;
	const int CURRENT_MAP_VERSION = 3;
    const float TILE_EXTRA_PIXELS = 1.0f;
    const int MAX_MONSTERS_DEFAULT = 99999;

	class CMap:  public IResource
	{
	public:
		CMap();
		virtual ~CMap();

		int GetVersion();
		sf::Vector2i GetStartPosition();
		const std::string & GetFilename();
		sf::Vector2<int> GetSize();
		std::vector<CTile*> * GetMapTiles();

		/* IResource members */

		std::string GetType();
		bool Load(std::map<std::string,std::string>& argv);
        bool Save(const std::string &filename);
        void Serialize(std::stringstream &out);
		void Drop();

        void RespawnMapObjects(bool loadCompleteMap);
		void RespawnDoodahs();
		void CullVisibility( const sf::FloatRect &  viewRectangle );

        const std::string &GetOrCreateTileCode(const std::string &path);
        void SetTile(int x,int y, const std::string &code);

		void AddDoodah(const std::string& file,float x,float y,int z,float rot,float scale,bool create=true);
		void EraseDoodah(int doodahDescriptorId);

		const std::string &GetOrCreateMapObjectCode(CPhysicalTemplate* t);
        void AddMapObject(const std::string& code,float x,float y,float rot,bool create=true, const std::string& name="");
		void EraseMapObject(int mapObjectDescriptorId);

        void AddRegion(CRegionDescriptor* region, bool show);
        void EraseRegion(int regionDescriptorId);
        CRegionDescriptor* GetRegionDescriptorById(int regionDescriptorId);

        int GetMaxLivingMonsters() { return mMaxLivingMonsters; }
        sf::Vector2f GetExitPos();

        // uzywane przez edytor
        void ShowInvisibleWalls(bool show = true);
        // WYMAGA zapisu i ponownego wczytania mapy!
        bool Resize(int x, int y, const std::string& defaultTile = "");

	private:

		std::vector<CTile*> * mFields;

		struct MapHeader{
			int Version;
			int Width;
			int Height;
			int TileImagesCount;

			sf::Vector2i StartPosition;
		};

		MapHeader * mMapHeader;

		FILE * mMapFileHandle;

		std::vector<CMapTileType *> mTileTypes;
		std::vector<CMapObjectType *> mMapObjectTypes;

        std::vector<CMapObjectDescriptor *> mMapObjectDescriptors;
		std::vector<CDoodahDescriptor *> mDoodahDescriptors;
        std::vector<CRegionDescriptor *> mRegionDescriptors;

		std::string mMapFilename;
		sf::Vector2<int> m_size;

		sf::IntRect mViewRectangle;

        bool LoadFromXML(const std::string & filename);

        void ClearTiles();
		void ClearMapObjects();
		void ClearDoodahs();

        int GetTileTypeIndex(const std::string &str);
        int GetMapObjectTypeIndex(const std::string &str);

        int mMaxLivingMonsters;

#ifdef __EDITOR__
        friend class ::CEditorWnd;
        friend class ::CTileResource;
#endif
	};

}
#endif//__CMAP_H__
