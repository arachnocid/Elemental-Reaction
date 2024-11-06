#include "logger.h"
#include <cmath>

class PluginParameter {
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
    static RE::TESGlobal    *overloadDmgFactor;
    static RE::TESGlobal    *meltDmgFactor;
    static RE::TESGlobal    *superconductivityDmgFactor;
    static RE::TESGlobal    *playerOverloadDmgFactor;
    static RE::TESGlobal    *playerMeltDmgFactor;
    static RE::TESGlobal    *playerSuperconductivityDmgFactor;
    static RE::TESGlobal    *overloadStagger;
    static RE::TESGlobal    *meltResistReduce;
    static RE::TESGlobal    *superconductivityArmorReduce;
    static RE::TESGlobal    *playerOverloadStagger;
    static RE::TESGlobal    *playerMeltResistReduce;
    static RE::TESGlobal    *playerSuperconductivityArmorReduce;
    static RE::TESGlobal    *playerDmgIncurredCap;

    static std::vector<RE::BGSKeyword *>    elementalDmgKeywords;
};

RE::BGSKeyword  *PluginParameter::mgDmgFireKeyword = nullptr;
RE::BGSKeyword  *PluginParameter::mgDmgFrostKeyword = nullptr;
RE::BGSKeyword  *PluginParameter::mgDmgShockKeyword = nullptr;
RE::FormID      PluginParameter::fireAttachmentEffectID = 0x0;
RE::FormID      PluginParameter::frostAttachmentEffectID = 0x0;
RE::FormID      PluginParameter::shockAttachmentEffectID = 0x0;
RE::SpellItem   *PluginParameter::fireAttachmentSpell = nullptr;
RE::SpellItem   *PluginParameter::frostAttachmentSpell = nullptr;
RE::SpellItem   *PluginParameter::shockAttachmentSpell = nullptr;
RE::SpellItem   *PluginParameter::fireShockDamageSpell = nullptr;
RE::SpellItem   *PluginParameter::fireShockDamageNoCasterSpell = nullptr;
RE::SpellItem   *PluginParameter::fireShockStaggerSpell = nullptr;
RE::SpellItem   *PluginParameter::fireFrostDamageSpell = nullptr;
RE::SpellItem   *PluginParameter::fireFrostDamageNoCasterSpell = nullptr;
RE::SpellItem   *PluginParameter::fireFrostResistModifierSpell = nullptr;
RE::SpellItem   *PluginParameter::frostShockDamageSpell = nullptr;
RE::SpellItem   *PluginParameter::frostShockDamageNoCasterSpell = nullptr;
RE::SpellItem   *PluginParameter::frostShockResistModifierSpell = nullptr;
RE::TESGlobal   *PluginParameter::overloadDmgFactor = nullptr;
RE::TESGlobal   *PluginParameter::meltDmgFactor = nullptr;
RE::TESGlobal   *PluginParameter::superconductivityDmgFactor = nullptr;
RE::TESGlobal   *PluginParameter::playerOverloadDmgFactor = nullptr;
RE::TESGlobal   *PluginParameter::playerMeltDmgFactor = nullptr;
RE::TESGlobal   *PluginParameter::playerSuperconductivityDmgFactor = nullptr;
RE::TESGlobal   *PluginParameter::overloadStagger = nullptr;
RE::TESGlobal   *PluginParameter::meltResistReduce = nullptr;
RE::TESGlobal   *PluginParameter::superconductivityArmorReduce = nullptr;
RE::TESGlobal   *PluginParameter::playerOverloadStagger = nullptr;
RE::TESGlobal   *PluginParameter::playerMeltResistReduce = nullptr;
RE::TESGlobal   *PluginParameter::playerSuperconductivityArmorReduce = nullptr;
RE::TESGlobal   *PluginParameter::playerDmgIncurredCap = nullptr;

std::vector<RE::BGSKeyword *>   PluginParameter::elementalDmgKeywords = {};

void MessageHandler(SKSE::MessagingInterface::Message* a_message) {
	switch (a_message->type) {
	case SKSE::MessagingInterface::kPostLoad:
		break;
	case SKSE::MessagingInterface::kPostPostLoad:
		break;
	case SKSE::MessagingInterface::kDataLoaded: {
        auto handler = RE::TESDataHandler::GetSingleton();
        PluginParameter::mgDmgFireKeyword = handler->LookupForm<RE::BGSKeyword>(0x1cead, "skyrim.esm");
        PluginParameter::mgDmgFrostKeyword = handler->LookupForm<RE::BGSKeyword>(0x1ceae, "skyrim.esm");
        PluginParameter::mgDmgShockKeyword = handler->LookupForm<RE::BGSKeyword>(0x1ceaf, "skyrim.esm");
        PluginParameter::fireAttachmentEffectID = handler->LookupFormID(0xd95, "Elemental Reaction.esm");
        PluginParameter::frostAttachmentEffectID = handler->LookupFormID(0xd68, "Elemental Reaction.esm");
        PluginParameter::shockAttachmentEffectID = handler->LookupFormID(0xd94, "Elemental Reaction.esm");
        PluginParameter::fireAttachmentSpell = handler->LookupForm<RE::SpellItem>(0xd97, "Elemental Reaction.esm");
        PluginParameter::frostAttachmentSpell = handler->LookupForm<RE::SpellItem>(0xd9e, "Elemental Reaction.esm");
        PluginParameter::shockAttachmentSpell = handler->LookupForm<RE::SpellItem>(0xd9f, "Elemental Reaction.esm");
        PluginParameter::fireShockDamageSpell = handler->LookupForm<RE::SpellItem>(0xdaa, "Elemental Reaction.esm");
        PluginParameter::fireShockDamageNoCasterSpell = handler->LookupForm<RE::SpellItem>(0xd9c, "Elemental Reaction.esm");
        PluginParameter::fireShockStaggerSpell = handler->LookupForm<RE::SpellItem>(0xda7, "Elemental Reaction.esm");
        PluginParameter::fireFrostDamageSpell = handler->LookupForm<RE::SpellItem>(0xdb0, "Elemental Reaction.esm");
        PluginParameter::fireFrostDamageNoCasterSpell = handler->LookupForm<RE::SpellItem>(0xdb3, "Elemental Reaction.esm");
        PluginParameter::fireFrostResistModifierSpell = handler->LookupForm<RE::SpellItem>(0xdb1, "Elemental Reaction.esm");
        PluginParameter::frostShockDamageSpell = handler->LookupForm<RE::SpellItem>(0xdb9, "Elemental Reaction.esm");
        PluginParameter::frostShockDamageNoCasterSpell = handler->LookupForm<RE::SpellItem>(0xdba, "Elemental Reaction.esm");
        PluginParameter::frostShockResistModifierSpell = handler->LookupForm<RE::SpellItem>(0xdb8, "Elemental Reaction.esm");
        PluginParameter::overloadDmgFactor = handler->LookupForm<RE::TESGlobal>(0xdbc, "Elemental Reaction.esm");
        PluginParameter::meltDmgFactor = handler->LookupForm<RE::TESGlobal>(0xdbd, "Elemental Reaction.esm");
        PluginParameter::superconductivityDmgFactor = handler->LookupForm<RE::TESGlobal>(0xdbe, "Elemental Reaction.esm");
        PluginParameter::playerOverloadDmgFactor = handler->LookupForm<RE::TESGlobal>(0xdbf, "Elemental Reaction.esm");
        PluginParameter::playerMeltDmgFactor = handler->LookupForm<RE::TESGlobal>(0xdc0, "Elemental Reaction.esm");
        PluginParameter::playerSuperconductivityDmgFactor = handler->LookupForm<RE::TESGlobal>(0xdc1, "Elemental Reaction.esm");
        PluginParameter::overloadStagger = handler->LookupForm<RE::TESGlobal>(0xdc2, "Elemental Reaction.esm");
        PluginParameter::meltResistReduce = handler->LookupForm<RE::TESGlobal>(0xdc3, "Elemental Reaction.esm");
        PluginParameter::superconductivityArmorReduce = handler->LookupForm<RE::TESGlobal>(0xdc4, "Elemental Reaction.esm");
        PluginParameter::playerOverloadStagger = handler->LookupForm<RE::TESGlobal>(0xdc7, "Elemental Reaction.esm");
        PluginParameter::playerMeltResistReduce = handler->LookupForm<RE::TESGlobal>(0xdc5, "Elemental Reaction.esm");
        PluginParameter::playerSuperconductivityArmorReduce = handler->LookupForm<RE::TESGlobal>(0xdc6, "Elemental Reaction.esm");
        PluginParameter::playerDmgIncurredCap = handler->LookupForm<RE::TESGlobal>(0xdc8, "Elemental Reaction.esm");
        logger::info("OverloadDmgFactor: {}", PluginParameter::overloadDmgFactor->value);
        logger::info("MeltDmgFactor: {}", PluginParameter::meltDmgFactor->value);
        logger::info("SuperconductivityDmgFactor: {}", PluginParameter::superconductivityDmgFactor->value);
        logger::info("PlayerOverloadDmgFactor: {}", PluginParameter::playerOverloadDmgFactor->value);
        logger::info("PlayerMeltDmgFactor: {}", PluginParameter::playerMeltDmgFactor->value);
        logger::info("PlayerSuperconductivityDmgFactor: {}", PluginParameter::playerSuperconductivityDmgFactor->value);
        logger::info("OverloadStagger: {}", PluginParameter::overloadStagger->value);
        logger::info("PlayerOverloadStagger: {}", PluginParameter::playerOverloadStagger->value);
        logger::info("MeltResistReduce: {}", PluginParameter::meltResistReduce->value);
        logger::info("SuperconductivityArmorReduce: {}", PluginParameter::superconductivityArmorReduce->value);
        logger::info("PlayerMeltResistReduce->value: {}", PluginParameter::playerMeltResistReduce->value);
        logger::info("PlayerSuperconductivityArmorReduce: {}", PluginParameter::playerSuperconductivityArmorReduce->value);
        logger::info("PlayerDmgIncurredCap->value: {}", PluginParameter::playerDmgIncurredCap->value);
        PluginParameter::elementalDmgKeywords = {
            PluginParameter::mgDmgFireKeyword,
            PluginParameter::mgDmgFrostKeyword,
            PluginParameter::mgDmgShockKeyword
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

float calDmg(int a_actorLevel, double a_damageFactor ,bool a_isPlayer, double a_playerDamageFactor, int a_damageCap) {
    double damage = a_isPlayer ? a_playerDamageFactor * std::log(1 + a_actorLevel / 10) + 10 : a_damageFactor * std::log(1 + a_actorLevel / 10) + 10;
    damage = (a_isPlayer and damage > a_damageCap) ? a_damageCap : damage;
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
        if ((*it)->GetBaseObject()->GetFormID() == PluginParameter::fireAttachmentEffectID) {
            array[0] = 1;
        } else if ((*it)->GetBaseObject()->GetFormID() == PluginParameter::frostAttachmentEffectID) {
            array[1] = 1;
        } else if ((*it)->GetBaseObject()->GetFormID() == PluginParameter::shockAttachmentEffectID) {
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
                magnitude = calDmg(casterLevel, static_cast<int>(PluginParameter::meltDmgFactor->value), isPlayer(targetID), static_cast<int>(PluginParameter::playerMeltDmgFactor->value), static_cast<int>(PluginParameter::playerDmgIncurredCap->value));
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::fireFrostResistModifierSpell, false, nullptr, 1, false, static_cast<float>(isPlayer(targetID)?PluginParameter::playerMeltResistReduce->value:PluginParameter::meltResistReduce->value), nullptr);
                if (a_event->caster and a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    a_event->caster.get()->As<RE::Actor>()->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::fireFrostDamageSpell, false, a_event->target.get(), 1, false, magnitude, nullptr);
                } else {
                    target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::fireFrostDamageNoCasterSpell, false, nullptr, 1, false, magnitude, nullptr);
                }
                logger::info("Melt on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID, magnitude);
                break;
            }
            case 0b101: {   // fire shock
                magnitude = calDmg(casterLevel, static_cast<int>(PluginParameter::overloadDmgFactor->value), isPlayer(targetID), static_cast<int>(PluginParameter::playerOverloadDmgFactor->value), static_cast<int>(PluginParameter::playerDmgIncurredCap->value));
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::fireShockStaggerSpell, false, nullptr, 1, false, 0.25, nullptr);
                if (a_event->caster and a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    a_event->caster.get()->As<RE::Actor>()->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::fireShockDamageSpell, false, a_event->target.get(), 1, false, magnitude, nullptr);
                } else {
                    target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::fireShockDamageNoCasterSpell, false, nullptr, 1, false, magnitude, nullptr);
                }
                logger::info("Overloaded on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID, magnitude);
                break;
            }
            case 0b110: {    // frost shock
                magnitude = calDmg(casterLevel, static_cast<int>(PluginParameter::superconductivityDmgFactor->value), isPlayer(targetID), static_cast<int>(PluginParameter::playerSuperconductivityDmgFactor->value), static_cast<int>(PluginParameter::playerDmgIncurredCap->value));
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::frostShockResistModifierSpell, false, nullptr, 1, false, static_cast<float>(isPlayer(targetID)?PluginParameter::playerSuperconductivityArmorReduce->value:PluginParameter::superconductivityArmorReduce->value), nullptr);
                if (a_event->caster and a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    a_event->caster.get()->As<RE::Actor>()->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::frostShockDamageSpell, false, a_event->target.get(), 1, false, magnitude, nullptr);
                } else {
                    target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::frostShockDamageNoCasterSpell, false, nullptr, 1, false, magnitude, nullptr);
                }
                logger::info("Superconductivity on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID, magnitude);
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

        if (a_event->target and a_event->target.get()->GetMagicTarget()->MagicTargetIsActor() and magicEffect->HasKeywordInArray(PluginParameter::elementalDmgKeywords, false)) {
            auto target = a_event->target.get()->As<RE::Actor>();

            if (magicEffect->HasKeyword(PluginParameter::mgDmgFireKeyword)) {
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::fireAttachmentSpell, false, nullptr, 1, false, 0, target);
            }
            if (magicEffect->HasKeyword(PluginParameter::mgDmgFrostKeyword)) {
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::frostAttachmentSpell, false, nullptr, 1, false, 0, target);
            }
            if (magicEffect->HasKeyword(PluginParameter::mgDmgShockKeyword)) {
                target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(PluginParameter::shockAttachmentSpell, false, nullptr, 1, false, 0, target);
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
