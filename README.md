# MyDiamond
A simple demo of 2D PUZ game. However, constructing by a self-designed gameplay framework, which taking a page from ***Unreal Engine's Gameplay Framework***. 

## Game Features

- Move character in the map
- Grab and throw diamonds to eliminate same diamonds
- Diamonds will be generated each turn
- DO NOT LET DIAMONDS MEET DEADLINE!!!

## Build Project

- **From source code**

Use Visual Studio to build the project

- **Get release version**

## Project Structure

![UML](public/Images/Project_ MD.jpg)

### MDGameInstance

A instance of the game. 

Generate **GameMode**.

Create a game iteration.

```cpp
class MDGameInstance
{
public:
    MDGameInstance();
	
    // ...

private:
    void CreateGameMode();
   	
	// ...
};
```

Game iteration

```cpp
class MDGameInstance
{
    // ...
    
protected:
    virtual void OnEndPlay();
    virtual void OnEnterNextTurn() const;
    virtual void OnGameOver();
    virtual void OnGameStart();
    virtual void OnBeginPlay();
    virtual void OnUpdata();
    virtual void OnSaveGame();
   	
	// ...
};
```

A global variable.

```cpp
extern unique_ptr<MDGameInstance> GameInstance;
```

### MDGameMode

A Config contains information of **PlayerController, PlayerState, Pawn, GameState**.

```cpp
class MDGameMode
{
	// ...

private:
    shared_ptr<MDPawn> DefaultPawn;
    shared_ptr<MDPlayerController> PlayerController;
    shared_ptr<MDPlayerState> PlayerState;
    shared_ptr<MDGameState> GameState;
    shared_ptr<MDUserWidget> HUD;
};
```

### MDScene

A singleton class. 

As actors container.

```cpp
class MDScene final
{
public:
    typedef vector<vector<shared_ptr<MDActor>>> Map;
    
    // ...

public:
    static MDScene* Get();
    
    // ...

private:
    static MDScene* SceneInstance;

    /* Each slot can contain an actor */
    Map Slots;

    /* A list recording all actors which have been registered */
    unordered_set<shared_ptr<MDActor>> ActorSet;
};
```

### MDActor

Base class of all actors.

Containing SceneComponent which means that it has the information of position.

Can be stored by **MDScene**.

```cpp
class MDActor
{
	// ...

public:
    std::shared_ptr<MDSceneComponent> SceneComponent;
};
```

### MDPlayerController

Controller can possess a pawn.

Receiving the player's input and deal with it, powered by **InputComponent**

```cpp
class MDPlayerController : enable_shared_from_this<MDPlayerController>
{
public:
    // ...
    
    void Possess(const shared_ptr<MDPawn>& PossessedPawn);
    void UnPossess();
    void OnPawnMove(EMoveDirection Direction) const;
    shared_ptr<MDInputComponent> InputComponent;
    
    // ...

private:
    shared_ptr<MDPlayerState> PlayerState;
    shared_ptr<MDPawn> PossessedPawn;
};
```



### MDPawn

An actor that can be possessed by **controller**. 

Acting according to controller's command.

```cpp
class MDPawn : public MDActor, public enable_shared_from_this<MDPawn>
{
public:
    void Move(EMoveDirection Direction);
    
    // ...
};
```

### MDPlayerState

Information of Pawn.

### MDGameState

Information of the whole game.

### MDUserWidget

Construct UI part of the game. 

Giving some render interfaces.

```cpp
class MDUserWidget
{
public:
    void Render() const;
    void RenderQuitUI() const;

private:
    void RenderHeader() const;
    void RenderGameInfo() const;
    static void RenderNewLine();

	// ...
};
```

### MDInputComponent

 Handle player's input and generate **input commands**.

```cpp
class MDInputComponent
{
public:
    MDInputComponent(const weak_ptr<MDPlayerController>& OwnerCache);
    shared_ptr<IInputCommand> HandleInput() const;
};
```

### IInputCommand

Send a message to **controller** to deal with the player's input.

```cpp
class IInputCommand
{
public:
    virtual ~IInputCommand() = default;
    virtual void Execute(const shared_ptr<MDPlayerController>& PlayerController) = 0;
};
```

### MDUserWidget

Create UI for the process of game.

```cpp
class MDUserWidget
{
public:
    // ...
    
    virtual void Render() const;
	
    // ...
};
```

### MDSaveGame

Contain data to serialize and deserialize.

```cpp
struct MDSaveGame
{
    float BestScore;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(BestScore);
    }
};
```

