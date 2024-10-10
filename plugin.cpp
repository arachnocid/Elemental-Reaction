#include "logger.h"

class GlobalValue {
public:
    static RE::BGSKeyword   *mgDmgFireKeyword;
    static RE::BGSKeyword   *mgDmgFrostKeyword;
    static RE::BGSKeyword   *mgDmgShockKeyword;
    static RE::FormID       fireAttachmentEffectID;
    static RE::FormID       frostAttachmentEffectID;
    static RE::FormID       shockAttachmentEffectID;
    static RE::SpellItem    *fireAttachmentSpell;
    static RE::SpellItem    *frostAttachmentSpell;
    static RE::SpellItem    *shockAttachmentSpell;
    static RE::SpellItem    *fireShockDamageSpell;
    static RE::SpellItem    *fireShockDamageNoCasterSpell;
    static RE::SpellItem    *fireShockStaggerSpell;
    static RE::SpellItem    *fireFrostDamageSpell;
    static RE::SpellItem    *fireFrostDamageNoCasterSpell;
    static RE::SpellItem    *fireFrostResistModifierSpell;
    static RE::SpellItem    *frostShockDamageSpell;
    static RE::SpellItem    *frostShockDamageNoCasterSpell;
    static RE::SpellItem    *frostShockResistModifierSpell;

    static float            reactionBaseDmg;

    static std::vector<RE::BGSKeyword *>    elementalDmgKeywords;
};

RE::BGSKeyword  *GlobalValue::mgDmgFireKeyword = nullptr;
RE::BGSKeyword  *GlobalValue::mgDmgFrostKeyword = nullptr;
RE::BGSKeyword  *GlobalValue::mgDmgShockKeyword = nullptr;
RE::FormID      GlobalValue::fireAttachmentEffectID = 0x0;
RE::FormID      GlobalValue::frostAttachmentEffectID = 0x0;
RE::FormID      GlobalValue::shockAttachmentEffectID = 0x0;
RE::SpellItem   *GlobalValue::fireAttachmentSpell = nullptr;
RE::SpellItem   *GlobalValue::frostAttachmentSpell = nullptr;
RE::SpellItem   *GlobalValue::shockAttachmentSpell = nullptr;
RE::SpellItem   *GlobalValue::fireShockDamageSpell = nullptr;
RE::SpellItem   *GlobalValue::fireShockDamageNoCasterSpell = nullptr;
RE::SpellItem   *GlobalValue::fireShockStaggerSpell = nullptr;
RE::SpellItem   *GlobalValue::fireFrostDamageSpell = nullptr;
RE::SpellItem   *GlobalValue::fireFrostDamageNoCasterSpell = nullptr;
RE::SpellItem   *GlobalValue::fireFrostResistModifierSpell = nullptr;
RE::SpellItem   *GlobalValue::frostShockDamageSpell = nullptr;
RE::SpellItem   *GlobalValue::frostShockDamageNoCasterSpell = nullptr;
RE::SpellItem   *GlobalValue::frostShockResistModifierSpell = nullptr;

float           GlobalValue::reactionBaseDmg = 10;

std::vector<RE::BGSKeyword *>   GlobalValue::elementalDmgKeywords = {};

void MessageHandler(SKSE::MessagingInterface::Message* a_message) {
	switch (a_message->type) {
	case SKSE::MessagingInterface::kPostLoad:
		break;
	case SKSE::MessagingInterface::kPostPostLoad:
		break;
	case SKSE::MessagingInterface::kDataLoaded: {
        auto handler = RE::TESDataHandler::GetSingleton();
        GlobalValue::mgDmgFireKeyword = handler->LookupForm<RE::BGSKeyword>(0x1cead, "skyrim.esm");
        GlobalValue::mgDmgFrostKeyword = handler->LookupForm<RE::BGSKeyword>(0x1ceae, "skyrim.esm");
        GlobalValue::mgDmgShockKeyword = handler->LookupForm<RE::BGSKeyword>(0x1ceaf, "skyrim.esm");
        GlobalValue::fireAttachmentEffectID = handler->LookupFormID(0xd95, "Elemental Reaction.esm");
        GlobalValue::frostAttachmentEffectID = handler->LookupFormID(0xd68, "Elemental Reaction.esm");
        GlobalValue::shockAttachmentEffectID = handler->LookupFormID(0xd94, "Elemental Reaction.esm");
        GlobalValue::fireAttachmentSpell = handler->LookupForm<RE::SpellItem>(0xd97, "Elemental Reaction.esm");
        GlobalValue::frostAttachmentSpell = handler->LookupForm<RE::SpellItem>(0xd9e, "Elemental Reaction.esm");
        GlobalValue::shockAttachmentSpell = handler->LookupForm<RE::SpellItem>(0xd9f, "Elemental Reaction.esm");
        GlobalValue::fireShockDamageSpell = handler->LookupForm<RE::SpellItem>(0xdaa, "Elemental Reaction.esm");
        GlobalValue::fireShockDamageNoCasterSpell = handler->LookupForm<RE::SpellItem>(0xd9c, "Elemental Reaction.esm");
        GlobalValue::fireShockStaggerSpell = handler->LookupForm<RE::SpellItem>(0xda7, "Elemental Reaction.esm");
        GlobalValue::fireFrostDamageSpell = handler->LookupForm<RE::SpellItem>(0xdb0, "Elemental Reaction.esm");
        GlobalValue::fireFrostDamageNoCasterSpell = handler->LookupForm<RE::SpellItem>(0xdb3, "Elemental Reaction.esm");
        GlobalValue::fireFrostResistModifierSpell = handler->LookupForm<RE::SpellItem>(0xdb1, "Elemental Reaction.esm");
        GlobalValue::frostShockDamageSpell = handler->LookupForm<RE::SpellItem>(0xdb9, "Elemental Reaction.esm");
        GlobalValue::frostShockDamageNoCasterSpell = handler->LookupForm<RE::SpellItem>(0xdba, "Elemental Reaction.esm");
        GlobalValue::frostShockResistModifierSpell = handler->LookupForm<RE::SpellItem>(0xdb8, "Elemental Reaction.esm");
        GlobalValue::elementalDmgKeywords = {
            GlobalValue::mgDmgFireKeyword,
            GlobalValue::mgDmgFrostKeyword,
            GlobalValue::mgDmgShockKeyword
        };
		break;
    }
	default:
		break;
	}
}

std::vector<int> generateZeroArray(int N) {
    return std::vector<int>(N, 0);
}

std::vector<std::pair<int, int>> findAllPairs(const std::vector<int>& array) {
    std::vector<std::pair<int, int>> pairs;
    size_t N = array.size();

    for (int i = 0; i < N; ++i) {
        if (array[i] == 1) {
            for (int j = i + 1; j < N; ++j) {
                if (array[j] == 1) {
                    pairs.push_back({i, j});
                }
            }
        }
    }

    return pairs;
}

bool isPlayer(RE::FormID a_id) {
    return a_id == 0x14;
}

float calDmgFireShock(int a_actorLevel, double a_baseDamage ,bool a_isPlayer) {
    double damage = (a_actorLevel < 25) ? a_baseDamage * (a_actorLevel * a_actorLevel / 2 + 25) * 0.015 : a_baseDamage * (25 * 25 / 2 + 25) * 0.015 + a_actorLevel - 25;
    damage = (a_isPlayer and damage > 10) ? 10 : damage;
    return static_cast<float>(damage);
}

float calDmgFireFrost(int a_actorLevel, double a_baseDamage, bool a_isPlayer) {
    double damage = (a_actorLevel < 25) ? a_baseDamage * (a_actorLevel * a_actorLevel / 2 + 25) * 0.015 : a_baseDamage * (25 * 25 / 2 + 25) * 0.015 + a_actorLevel - 25;
    damage = (a_isPlayer and damage > 10) ? 10 : damage;
    return static_cast<float>(damage);
}

float calDmgFrostShock(int a_actorLevel, double a_baseDamage, bool a_isPlayer) {
    double damage = (a_actorLevel < 25) ? a_baseDamage * (a_actorLevel * a_actorLevel / 2 + 25) * 0.015 : a_baseDamage * (25 * 25 / 2 + 25) * 0.015 + a_actorLevel - 25;
    damage = (a_isPlayer and damage > 10) ? 10 : damage;
    return static_cast<float>(damage);
}

void ElementalReaction(const RE::TESMagicEffectApplyEvent* a_event) {
    /*  index of element in array
        fire = 0, frost = 1, shock = 2
    */
    std::vector<int> array = generateZeroArray(3);
    auto effectList = a_event->target.get()->GetMagicTarget()->GetActiveEffectList();
    auto target = a_event->target.get()->As<RE::Actor>();
    auto targetID = a_event->target.get()->GetFormID();
    int casterLevel;

    if (a_event->caster and a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()){
        casterLevel = static_cast<int>(a_event->caster.get()->As<RE::Actor>()->GetLevel());
    } else {
        casterLevel = 1;
    }

    for (auto it = effectList->begin(); it != effectList->end(); ++it) {
        if ((*it)->GetBaseObject()->GetFormID() == GlobalValue::fireAttachmentEffectID) {
            array[0] = 1;
        } else if ((*it)->GetBaseObject()->GetFormID() == GlobalValue::frostAttachmentEffectID) {
            array[1] = 1;
        } else if ((*it)->GetBaseObject()->GetFormID() == GlobalValue::shockAttachmentEffectID) {
            array[2] = 1;
        }
    }
    std::vector<std::pair<int, int>> pairs = findAllPairs(array);

    int binary_sum;
    float magnitude;
    for (const auto& pair : pairs) {
        binary_sum = (1 << pair.first) + (1 << pair.second);
        switch (binary_sum) {
            case 0b11: {    // fire frost
                magnitude = calDmgFireFrost(casterLevel, GlobalValue::reactionBaseDmg, isPlayer(targetID));
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::fireFrostResistModifierSpell, false, nullptr, 1, false, static_cast<float>(isPlayer(targetID)?4:40), nullptr);
                if (a_event->caster and a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    a_event->caster.get()->As<RE::Actor>()->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::fireFrostDamageSpell, false, a_event->target.get(), 1, false, magnitude, nullptr);
                } else {
                    target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::fireFrostDamageNoCasterSpell, false, nullptr, 1, false, magnitude, nullptr);
                }
                // logger::info("Melt on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID, magnitude);
                break;
            }
            case 0b101: {   // fire shock
                magnitude = calDmgFireShock(casterLevel, GlobalValue::reactionBaseDmg, isPlayer(targetID));
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::fireShockStaggerSpell, false, nullptr, 1, false, 0.25, nullptr);
                if (a_event->caster and a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    a_event->caster.get()->As<RE::Actor>()->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::fireShockDamageSpell, false, a_event->target.get(), 1, false, magnitude, nullptr);
                } else {
                    target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::fireShockDamageNoCasterSpell, false, nullptr, 1, false, magnitude, nullptr);
                }
                // logger::info("Overloaded on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID, magnitude);
                break;
            }
            case 0b110: {    // frost shock
                magnitude = calDmgFrostShock(casterLevel, GlobalValue::reactionBaseDmg, isPlayer(targetID));
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::frostShockResistModifierSpell, false, nullptr, 1, false, static_cast<float>(isPlayer(targetID)?33:333), nullptr);
                if (a_event->caster and a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    a_event->caster.get()->As<RE::Actor>()->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::frostShockDamageSpell, false, a_event->target.get(), 1, false, magnitude, nullptr);
                } else {
                    target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::frostShockDamageNoCasterSpell, false, nullptr, 1, false, magnitude, nullptr);
                }
                // logger::info("Superconductivity on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID, magnitude);
                break;
            }
            default:
                break;
        }
    }
}

struct ElementalReactionEventSink : public RE::BSTEventSink<RE::TESMagicEffectApplyEvent> {
    RE::BSEventNotifyControl ProcessEvent(const RE::TESMagicEffectApplyEvent* a_event, RE::BSTEventSource<RE::TESMagicEffectApplyEvent>*) {
        auto magicEffect = RE::TESForm::LookupByID<RE::EffectSetting>(a_event->magicEffect);

        if (a_event->target and a_event->target.get()->GetMagicTarget()->MagicTargetIsActor() and magicEffect->HasKeywordInArray(GlobalValue::elementalDmgKeywords, false)) {
            auto target = a_event->target.get()->As<RE::Actor>();

            if (magicEffect->HasKeyword(GlobalValue::mgDmgFireKeyword)) {
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::fireAttachmentSpell, false, nullptr, 1, false, 0, target);
            }
            if (magicEffect->HasKeyword(GlobalValue::mgDmgFrostKeyword)) {
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::frostAttachmentSpell, false, nullptr, 1, false, 0, target);
            }
            if (magicEffect->HasKeyword(GlobalValue::mgDmgShockKeyword)) {
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(GlobalValue::shockAttachmentSpell, false, nullptr, 1, false, 0, target);
            }

            ElementalReaction(a_event);
        }

        return RE::BSEventNotifyControl::kContinue;
    }
};

SKSEPluginLoad(const SKSE::LoadInterface *a_skse) {
    SKSE::Init(a_skse);

    SetupLog();
    logger::info("Game version : {}", a_skse->RuntimeVersion().string());

    const auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener(MessageHandler);

    auto eventSink = new ElementalReactionEventSink();
    auto* eventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
    eventSourceHolder->AddEventSink(eventSink);

    return true;
}
