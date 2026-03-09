#include "AnimGraphNode_SpiderIK.h"

FText UAnimGraphNode_SpiderIK::GetNodeTitle(
    ENodeTitleType::Type TitleType) const
{
    return FText::FromString("Spider IK (FABRIK)");
}

FText UAnimGraphNode_SpiderIK::GetTooltipText() const
{
    return FText::FromString(
        "Procedural spider leg IK using custom FABRIK solver.");
}

FText UAnimGraphNode_SpiderIK::GetControllerDescription() const
{
    return FText::FromString("Spider IK");
}