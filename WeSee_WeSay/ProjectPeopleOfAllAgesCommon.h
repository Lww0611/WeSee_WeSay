#ifndef PROJECTPEOPLEOFALLAGESCOMMON_H
#define PROJECTPEOPLEOFALLAGESCOMMON_H
#include <QString.h>
#include <QList.h>
#define  LIST_Alias QList<AliasList>
#define  LIST_AddressList QList<AddressList>
#define  LIST_OfficialList QList<OfficialList>
#define  LIST_ListOfOfficals QList<ListOfOfficals>
#define  LIST_DivisSocial QList<DivisSocial>
#define  LIST_FamillyRelation QList<FamillyRelation>
#define  LIST_SocialRelation QList<SocialRelation>
#define  LIST_ZhuShu QList<ZhuShu>
#define  LIST_Provenance QList<Provenance>
//基础信息
struct PeoPleBaseInfo
{
    QString Name;//< 名字
    QString PersonID;//<人物ID
    QString NaImputedBirth;//< 推算出生年
    QString Sex;//<性别
    QString Time;//<时期
    QString Alias;//<别名
    QString Birth;//生年
    QString DeathDays;//<卒年
    QString DieAtTheAge;//<享年
    QString NativePlace;//<籍贯
    QString Krorimaki;//<郡望
};

//别名列表
struct AliasList
{
    QString Number;//< 序号
    QString Type;//<类型
    QString Nmae;//<名字
    QString Comment;//< 备注
};

//地址列表
struct AddressList
{
    QString Number;//< 序号
    QString Type;//<类型
    QString Nmae;//<名字
    QString Birth;//始年
    QString DeathDays;//<终年
};

//入仕列表
struct OfficialList
{
    QString Number;//< 序号
    QString OfficialDoor;//< 入仕门
    QString OfficialDiff;//<入仕别
    QString OfficialAddress;//<入仕出处
    QString Comment;//< 备注
};

//任官列表
struct ListOfOfficals
{
    QString Number;//< 序号
    QString DisgrantClass;//< 除授类别
    QString OfficialName;//<官名
    QString OfficialAddress;//<任官地点
    QString OfficialTime;//<任官时间
    QString Address;//<出处
    QString Comment;//< 备注
};

//社会区分
struct DivisSocial
{
    QString Number;//< 序号
    QString SocialDivis;//< 社会区分
    QString Time;//<年代
    QString Address;//<出处
    QString Comment;//< 备注
};

//亲属关系
struct FamillyRelation
{
    QString Number;//< 序号
    QString Relation;//< 关系
    QString RelationPerson;//<关系人
    QString Address;//<出处
    QString Comment;//< 备注
};

//社会关系
struct SocialRelation
{
    QString Number;//< 序号
    QString Relation;//< 关系
    QString RelationPerson;//<关系人
    QString Address;//<出处
    QString Comment;//< 备注
};

//著述
struct ZhuShu
{
    QString Number;//< 序号
    QString Production;//< 作品
    QString ProductionTime;//<著作年代
    QString Role;//<角色
    QString Comment;//< 备注
};

//出处
struct Provenance
{
    QString Number;//< 序号
    QString Provenance_;//< 出处
    QString Comment;//< 备注
};
#endif // PROJECTPEOPLEOFALLAGESCOMMON_H
