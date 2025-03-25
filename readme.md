This is a simple game called GhostEscape developed using the SDL framework and GLM vector library.

## Project Structure

```
├── CMakeLists.txt          # CMake build configuration
├── affiliate/              # Affiliate components
│   ├── Collider.cpp        # Collision detection implementation
│   ├── Collider.h          # Collision detection header
│   ├── Sprite.cpp          # Sprite implementation
│   ├── Sprite.h            # Sprite header
│   ├── SpriteAnim.cpp      # Animation implementation
│   └── SpriteAnim.h        # Animation header
├── assets/                 # Game assets
│   ├── bgm/                # Background music
│   ├── data/               # Game data
│   ├── effect/             # Visual effects
│   ├── font/               # Font files
│   ├── sound/              # Sound effects
│   ├── sprite/             # Sprite images
│   └── UI/                 # UI elements
├── bin/                    # Binary executables
│   ├── ghostEscape-Windows-Debug.exe
│   └── ghostEscape-Windows-Debug.pdb
├── build/                  # Build artifacts
│   └── Debug/
├── core/                   # Core game engine
│   ├── Actor.cpp           # Actor implementation
│   ├── Actor.h             # Actor header
│   ├── AssetStore.cpp      # Asset management implementation
│   ├── AssetStore.h        # Asset management header
│   ├── defs.h              # Common definitions
│   ├── Game.cpp            # Main game implementation
│   ├── Game.h              # Main game header
│   ├── Object.cpp          # Base object implementation
│   ├── Object.h            # Base object header
│   ├── ObjectAffiliate.cpp # Object affiliate implementation
│   ├── ObjectAffiliate.h   # Object affiliate header
│   ├── ObjectScreen.h      # Screen object header
│   ├── ObjectWorld.cpp     # World object implementation
│   └── ObjectWorld.h       # World object header
├── raw/                    # Raw assets before processing
└── src/                    # Source code
```

## Reference
https://www.bilibili.com/video/BV1jf9XYQEhW