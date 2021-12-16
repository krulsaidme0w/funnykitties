namespace levelManager{
    class LevelManager {
    public:
        void levelList();
        void loadMap();

    private:
        string levels_storage;
        string current_map;

        void parsingLevelList();
        void parsingMap();
    };
}

