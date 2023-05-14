#pragma once
struct MDSaveGame
{
    float BestScore;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(BestScore);
    }
};

