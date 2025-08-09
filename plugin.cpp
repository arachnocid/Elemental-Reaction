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

void MessageHandler(SKSE::MessagingInterface::Message *a_message) {
    switch (a_message->type) {
        case SKSE::MessagingInterface::kDataLoaded: {
            auto handler = RE::TESDataHandler::GetSingleton();

            auto safeLookupKeyword = [&](RE::FormID id, const char *file) -> RE::BGSKeyword * {
                auto keyword = handler->LookupForm<RE::BGSKeyword>(id, file);
                if (!keyword) logger::warn("Keyword {:X} not found in {}", id, file);
                return keyword;
            };

            auto safeLookupSpell = [&](RE::FormID id, const char *file) -> RE::SpellItem * {
                auto spell = handler->LookupForm<RE::SpellItem>(id, file);
                if (!spell) logger::warn("Spell {:X} not found in {}", id, file);
                return spell;
            };

            auto safeLookupGlobal = [&](RE::FormID id, const char *file) -> RE::TESGlobal * {
                auto global = handler->LookupForm<RE::TESGlobal>(id, file);
                if (!global) logger::warn("Global {:X} not found in {}", id, file);
                return global;
            };

            PluginParameter::mgDmgFireKeyword = safeLookupKeyword(0x1cead, "Skyrim.esm");
            PluginParameter::mgDmgFrostKeyword = safeLookupKeyword(0x1ceae, "Skyrim.esm");
            PluginParameter::mgDmgShockKeyword = safeLookupKeyword(0x1ceaf, "Skyrim.esm");

            PluginParameter::fireAttachmentEffectID = handler->LookupFormID(0xd95, "Elemental Reaction.esm");
            PluginParameter::frostAttachmentEffectID = handler->LookupFormID(0xd68, "Elemental Reaction.esm");
            PluginParameter::shockAttachmentEffectID = handler->LookupFormID(0xd94, "Elemental Reaction.esm");

            PluginParameter::fireAttachmentSpell = safeLookupSpell(0xd97, "Elemental Reaction.esm");
            PluginParameter::frostAttachmentSpell = safeLookupSpell(0xd9e, "Elemental Reaction.esm");
            PluginParameter::shockAttachmentSpell = safeLookupSpell(0xd9f, "Elemental Reaction.esm");
            PluginParameter::fireShockDamageSpell = safeLookupSpell(0xdaa, "Elemental Reaction.esm");
            PluginParameter::fireShockDamageNoCasterSpell = safeLookupSpell(0xd9c, "Elemental Reaction.esm");
            PluginParameter::fireShockStaggerSpell = safeLookupSpell(0xda7, "Elemental Reaction.esm");
            PluginParameter::fireFrostDamageSpell = safeLookupSpell(0xdb0, "Elemental Reaction.esm");
            PluginParameter::fireFrostDamageNoCasterSpell = safeLookupSpell(0xdb3, "Elemental Reaction.esm");
            PluginParameter::fireFrostResistModifierSpell = safeLookupSpell(0xdb1, "Elemental Reaction.esm");
            PluginParameter::frostShockDamageSpell = safeLookupSpell(0xdb9, "Elemental Reaction.esm");
            PluginParameter::frostShockDamageNoCasterSpell = safeLookupSpell(0xdba, "Elemental Reaction.esm");
            PluginParameter::frostShockResistModifierSpell = safeLookupSpell(0xdb8, "Elemental Reaction.esm");

            PluginParameter::overloadDmgFactor = safeLookupGlobal(0xdbc, "Elemental Reaction.esm");
            PluginParameter::meltDmgFactor = safeLookupGlobal(0xdbd, "Elemental Reaction.esm");
            PluginParameter::superconductivityDmgFactor = safeLookupGlobal(0xdbe, "Elemental Reaction.esm");
            PluginParameter::playerOverloadDmgFactor = safeLookupGlobal(0xdbf, "Elemental Reaction.esm");
            PluginParameter::playerMeltDmgFactor = safeLookupGlobal(0xdc0, "Elemental Reaction.esm");
            PluginParameter::playerSuperconductivityDmgFactor = safeLookupGlobal(0xdc1, "Elemental Reaction.esm");
            PluginParameter::overloadStagger = safeLookupGlobal(0xdc2, "Elemental Reaction.esm");
            PluginParameter::meltResistReduce = safeLookupGlobal(0xdc3, "Elemental Reaction.esm");
            PluginParameter::superconductivityArmorReduce = safeLookupGlobal(0xdc4, "Elemental Reaction.esm");
            PluginParameter::playerOverloadStagger = safeLookupGlobal(0xdc7, "Elemental Reaction.esm");
            PluginParameter::playerMeltResistReduce = safeLookupGlobal(0xdc5, "Elemental Reaction.esm");
            PluginParameter::playerSuperconductivityArmorReduce = safeLookupGlobal(0xdc6, "Elemental Reaction.esm");
            PluginParameter::playerDmgIncurredCap = safeLookupGlobal(0xdc8, "Elemental Reaction.esm");

            PluginParameter::elementalDmgKeywords = {PluginParameter::mgDmgFireKeyword,
                                                     PluginParameter::mgDmgFrostKeyword,
                                                     PluginParameter::mgDmgShockKeyword};
            break;
        }
        default:
            break;
    }
}

std::vector<int> generateZeroArray(int N) {
    return std::vector<int>(N, 0);
}

std::vector<std::pair<int, int>> findAllPairs(const std::vector<int> &array) {
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

float calDmg(int a_actorLevel, double a_damageFactor, bool a_isPlayer, double a_playerDamageFactor,
                    int a_damageCap) {
    double damage = a_isPlayer ? a_playerDamageFactor * std::log(1 + a_actorLevel / 10) + 10 : a_damageFactor * std::log(1 + a_actorLevel / 10) + 10;
    damage = (a_isPlayer and damage > a_damageCap) ? a_damageCap : damage;
    return static_cast<float>(damage);
}

void ElementalReaction(const RE::TESMagicEffectApplyEvent *a_event) {
    if (!a_event || !a_event->target) return;

    auto targetRef = a_event->target.get();
    auto target = targetRef ? targetRef->As<RE::Actor>() : nullptr;
    if (!target) return;

    auto magicTarget = targetRef->GetMagicTarget();
    if (!magicTarget) return;

    auto effectList = magicTarget->GetActiveEffectList();
    if (!effectList) return;

    std::vector<int> array = generateZeroArray(3);
    auto targetID = targetRef->GetFormID();
    int casterLevel = 1;

    if (a_event->caster) {
        auto casterRef = a_event->caster.get();
        if (casterRef && casterRef->GetMagicTarget() && casterRef->GetMagicTarget()->MagicTargetIsActor()) {
            if (auto casterActor = casterRef->As<RE::Actor>()) {
                casterLevel = static_cast<int>(casterActor->GetLevel());
            }
        }
    }

    for (auto it = effectList->begin(); it != effectList->end(); ++it) {
        auto effect = *it;
        if (!effect || !effect->GetBaseObject()) continue;

        auto effectFormID = effect->GetBaseObject()->GetFormID();

        if (effectFormID == PluginParameter::fireAttachmentEffectID) {
            array[0] = 1;
        } else if (effectFormID == PluginParameter::frostAttachmentEffectID) {
            array[1] = 1;
        } else if (effectFormID == PluginParameter::shockAttachmentEffectID) {
            array[2] = 1;
        }
    }

    std::vector<std::pair<int, int>> pairs = findAllPairs(array);

    for (const auto &pair : pairs) {
        int binary_sum = (1 << pair.first) + (1 << pair.second);
        float magnitude;

        auto instantCasterTarget = target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant);

        switch (binary_sum) {
            case 0b11: {  // fire frost
                magnitude = calDmg(casterLevel, static_cast<int>(PluginParameter::meltDmgFactor->value),
                                   isPlayer(targetID), static_cast<int>(PluginParameter::playerMeltDmgFactor->value),
                                   static_cast<int>(PluginParameter::playerDmgIncurredCap->value));

                if (instantCasterTarget) {
                    instantCasterTarget->CastSpellImmediate(
                        PluginParameter::fireFrostResistModifierSpell, false, nullptr, 1, false,
                        static_cast<float>(isPlayer(targetID) ? PluginParameter::playerMeltResistReduce->value
                                                              : PluginParameter::meltResistReduce->value),
                        nullptr);
                }

                if (a_event->caster && a_event->caster.get()->GetMagicTarget() &&
                    a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    if (auto casterActor = a_event->caster.get()->As<RE::Actor>()) {
                        auto casterInstant = casterActor->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant);
                        if (casterInstant) {
                            casterInstant->CastSpellImmediate(PluginParameter::fireFrostDamageSpell, false, targetRef,
                                                              1, false, magnitude, nullptr);
                        }
                    }
                } else if (instantCasterTarget) {
                    instantCasterTarget->CastSpellImmediate(PluginParameter::fireFrostDamageNoCasterSpell, false,
                                                            nullptr, 1, false, magnitude, nullptr);
                }

                logger::info("Melt on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID, magnitude);
                break;
            }
            case 0b101: {  // fire shock
                magnitude =
                    calDmg(casterLevel, static_cast<int>(PluginParameter::overloadDmgFactor->value), isPlayer(targetID),
                           static_cast<int>(PluginParameter::playerOverloadDmgFactor->value),
                           static_cast<int>(PluginParameter::playerDmgIncurredCap->value));

                if (instantCasterTarget) {
                    instantCasterTarget->CastSpellImmediate(PluginParameter::fireShockStaggerSpell, false, nullptr, 1,
                                                            false, 0.25f, nullptr);
                }

                if (a_event->caster && a_event->caster.get()->GetMagicTarget() &&
                    a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    if (auto casterActor = a_event->caster.get()->As<RE::Actor>()) {
                        auto casterInstant = casterActor->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant);
                        if (casterInstant) {
                            casterInstant->CastSpellImmediate(PluginParameter::fireShockDamageSpell, false, targetRef,
                                                              1, false, magnitude, nullptr);
                        }
                    }
                } else if (instantCasterTarget) {
                    instantCasterTarget->CastSpellImmediate(PluginParameter::fireShockDamageNoCasterSpell, false,
                                                            nullptr, 1, false, magnitude, nullptr);
                }

                logger::info("Overloaded on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID, magnitude);
                break;
            }
            case 0b110: {  // frost shock
                magnitude = calDmg(casterLevel, static_cast<int>(PluginParameter::superconductivityDmgFactor->value),
                                   isPlayer(targetID),
                                   static_cast<int>(PluginParameter::playerSuperconductivityDmgFactor->value),
                                   static_cast<int>(PluginParameter::playerDmgIncurredCap->value));

                if (instantCasterTarget) {
                    instantCasterTarget->CastSpellImmediate(
                        PluginParameter::frostShockResistModifierSpell, false, nullptr, 1, false,
                        static_cast<float>(isPlayer(targetID)
                                               ? PluginParameter::playerSuperconductivityArmorReduce->value
                                               : PluginParameter::superconductivityArmorReduce->value),
                        nullptr);
                }

                if (a_event->caster && a_event->caster.get()->GetMagicTarget() &&
                    a_event->caster.get()->GetMagicTarget()->MagicTargetIsActor()) {
                    if (auto casterActor = a_event->caster.get()->As<RE::Actor>()) {
                        auto casterInstant = casterActor->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant);
                        if (casterInstant) {
                            casterInstant->CastSpellImmediate(PluginParameter::frostShockDamageSpell, false, targetRef,
                                                              1, false, magnitude, nullptr);
                        }
                    }
                } else if (instantCasterTarget) {
                    instantCasterTarget->CastSpellImmediate(PluginParameter::frostShockDamageNoCasterSpell, false,
                                                            nullptr, 1, false, magnitude, nullptr);
                }

                logger::info("Superconductivity on {}(FormID: {:#x}, magnitude: {})", target->GetName(), targetID,
                             magnitude);
                break;
            }
            default:
                break;
        }
    }
}


struct ElementalReactionEventSink : public RE::BSTEventSink<RE::TESMagicEffectApplyEvent> {
    RE::BSEventNotifyControl ProcessEvent(const RE::TESMagicEffectApplyEvent *a_event,
                                          RE::BSTEventSource<RE::TESMagicEffectApplyEvent> *) {
        if (!a_event || !a_event->target) return RE::BSEventNotifyControl::kContinue;

        auto target = a_event->target.get()->As<RE::Actor>();
        if (!target) return RE::BSEventNotifyControl::kContinue;

        auto magicTarget = target->GetMagicTarget();
        if (!magicTarget || !magicTarget->MagicTargetIsActor()) return RE::BSEventNotifyControl::kContinue;

        auto magicEffect = RE::TESForm::LookupByID<RE::EffectSetting>(a_event->magicEffect);
        if (!magicEffect || !magicEffect->HasKeywordInArray(PluginParameter::elementalDmgKeywords, false))
            return RE::BSEventNotifyControl::kContinue;

        if (magicEffect->HasKeyword(PluginParameter::mgDmgFireKeyword)) {
            if (auto caster = target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)) {
                if (PluginParameter::fireAttachmentSpell) {
                    caster->CastSpellImmediate(PluginParameter::fireAttachmentSpell, false, nullptr, 1, false, 0,
                                               target);
                }
            }
        }

        if (magicEffect->HasKeyword(PluginParameter::mgDmgFrostKeyword)) {
            if (auto caster = target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)) {
                if (PluginParameter::frostAttachmentSpell) {
                    caster->CastSpellImmediate(PluginParameter::frostAttachmentSpell, false, nullptr, 1, false, 0,
                                               target);
                }
            }
        }

        if (magicEffect->HasKeyword(PluginParameter::mgDmgShockKeyword)) {
            if (auto caster = target->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)) {
                if (PluginParameter::shockAttachmentSpell) {
                    caster->CastSpellImmediate(PluginParameter::shockAttachmentSpell, false, nullptr, 1, false, 0,
                                               target);
                }
            }
        }

        ElementalReaction(a_event);

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
