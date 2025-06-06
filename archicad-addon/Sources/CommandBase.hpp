#pragma once

#include "APIEnvir.h"
#include "ACAPinc.h"

#include "ObjectState.hpp"

#include <map>

enum class CommonSchema
{
    Used,
    NotUsed
};

class CommandBase : public API_AddOnCommand
{
public:
    CommandBase (CommonSchema commonSchema);

    virtual GS::String GetNamespace () const override final;
    virtual API_AddOnCommandExecutionPolicy GetExecutionPolicy () const override final;
    virtual void OnResponseValidationFailed (const GS::ObjectState& response) const override final;
#ifdef ServerMainVers_2600
    virtual bool IsProcessWindowVisible () const override final;
#endif
    virtual GS::Optional<GS::UniString> GetSchemaDefinitions () const override final;
    virtual GS::Optional<GS::UniString> GetInputParametersSchema () const override;
    virtual GS::Optional<GS::UniString> GetResponseSchema () const override;

private:
    CommonSchema mCommonSchema;
};

GS::ObjectState CreateErrorResponse (GSErrCode errorCode, const GS::UniString& errorMessage);
GS::ObjectState CreateFailedExecutionResult (GSErrCode errorCode, const GS::UniString& errorMessage);
GS::ObjectState CreateSuccessfulExecutionResult ();

API_Guid    GetGuidFromObjectState (const GS::ObjectState& os);
API_Guid    GetGuidFromArrayItem (const GS::String& idFieldName, const GS::ObjectState& os);
inline API_Guid GetGuidFromElementsArrayItem (const GS::ObjectState& os)        { return GetGuidFromArrayItem ("elementId", os); }
inline API_Guid GetGuidFromAttributesArrayItem (const GS::ObjectState& os)      { return GetGuidFromArrayItem ("attributeId", os); }
inline API_Guid GetGuidFromIssuesArrayItem (const GS::ObjectState& os)          { return GetGuidFromArrayItem ("issueId", os); }
inline API_Guid GetGuidFromNavigatorItemIdArrayItem (const GS::ObjectState& os) { return GetGuidFromArrayItem ("navigatorItemId", os); }
inline API_Guid GetGuidFromDatabaseArrayItem (const GS::ObjectState& os)        { return GetGuidFromArrayItem ("databaseId", os); }
bool   IsSame2DCoordinate (const GS::ObjectState& o1, const GS::ObjectState& o2);
API_Coord   Get2DCoordinateFromObjectState (const GS::ObjectState& objectState);
API_Coord3D Get3DCoordinateFromObjectState (const GS::ObjectState& objectState);
GS::ObjectState Create2DCoordinateObjectState (const API_Coord& c);
GS::ObjectState CreatePolyArcObjectState (const API_PolyArc& a);
inline GS::ObjectState CreateGuidObjectState (const API_Guid& guid) { return GS::ObjectState ("guid", APIGuidToString (guid)); }
inline GS::ObjectState CreateGuidObjectState (const GS::Guid& guid) { return GS::ObjectState ("guid", guid.ToUniString()); }
GS::ObjectState CreateIdObjectState (const GS::String& idFieldName, const API_Guid& guid);
inline GS::ObjectState CreateElementIdObjectState (const API_Guid& guid)   { return CreateIdObjectState ("elementId", guid); }
inline GS::ObjectState CreateAttributeIdObjectState (const API_Guid& guid) { return CreateIdObjectState ("attributeId", guid); }
inline GS::ObjectState CreateIssueIdObjectState (const API_Guid& guid)     { return CreateIdObjectState ("issueId", guid); }
inline GS::ObjectState CreateDatabaseIdObjectState (const API_Guid& guid)  { return CreateIdObjectState ("databaseId", guid); }

void AddPolygonFromMemoCoords (const API_Guid& elemGuid, GS::ObjectState& os, const GS::String& coordsFieldName, const GS::Optional<GS::String>& arcsFieldName = {});
void AddPolygonWithHolesFromMemoCoords (const API_Guid& elemGuid, GS::ObjectState& os, const GS::String& coordsFieldName, const GS::Optional<GS::String>& arcsFieldName, const GS::String& holesArrayFieldName, const GS::String& holeCoordsFieldName, const GS::Optional<GS::String>& holeArcsFieldName);

struct Story {
    Story (short _index, double _level)
        : index (_index)
        , level (_level)
    {}

    short  index;
    double level;
};
using Stories = std::map<short, Story>;

Stories GetStories ();
GS::Pair<short, double> GetFloorIndexAndOffset (const double zPos, const Stories& stories);
double GetZPos (const short floorIndex, const double offset, const Stories& stories);
GS::UniString GetElementTypeNonLocalizedName (API_ElemTypeID typeID);
API_ElemTypeID GetElementTypeFromNonLocalizedName (const GS::UniString& typeStr);