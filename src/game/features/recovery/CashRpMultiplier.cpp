#include "core/commands/LoopedCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	static FloatCommand _CashMultiplierInput{"cashmultiplierinput", "Cash Multiplier Input", "Cash Mulitplier (< 0 = 0 -> No Cash :c )", std::nullopt, std::nullopt, 1};
	static FloatCommand _RpMultiplierInput{"rpmultiplierinput", "RP Multiplier Input", "RP Mulitplier (< 0 = 0 -> No RP)", std::nullopt, std::nullopt, 1};
	static FloatCommand _ContactMissionCashMultiplierInput{"cmcashmultiplierinput", "Contact Mission Cash Multiplier Input", "Contact Mission Cash Mulitplier (< 0 = 0 -> No Mission Cash)", std::nullopt, std::nullopt, 1};
	static FloatCommand _ContactMissionRpMultiplierInput{"cmrpmultiplierinput", "Contact Mission RP Multiplier Input", "Contact Mission RP Mulitplier (< 0 = 0 -> No Mission RP)", std::nullopt, std::nullopt, 1};

	const int cm_CashBase = 20.0;
	const int cm_RPBase = 9.0;

	class OverrideCashMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_CashMultiplier{"Cash_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _CashMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CashMultiplier.IsReady())
				m_CashMultiplier.Set(state);
		}

		virtual void OnDisable() override
		{
			if (m_CashMultiplier.IsReady())
				m_CashMultiplier.Set(1.0f);
		}
	};

	class OverrideRPMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_XPMultiplier{"XP_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _RpMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_XPMultiplier.IsReady())
				m_XPMultiplier.Set(state);
		}

		virtual void OnDisable() override
		{
			if (m_XPMultiplier.IsReady())
				m_XPMultiplier.Set(1.0f);
		}
	};

	class OverrideCMCashMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_CM_CashMultiplier{"CONTACT_MISSION_CASH_BASE_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _ContactMissionCashMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CM_CashMultiplier.IsReady())
				m_CM_CashMultiplier.Set(cm_CashBase * state);
		}

		virtual void OnDisable() override
		{
			if (m_CM_CashMultiplier.IsReady())
				m_CM_CashMultiplier.Set(cm_CashBase);
		}
	};

	class OverrideCMRPMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_CM_XPMultiplier{"CONTACT_MISSION_RP_BASE_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _ContactMissionRpMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CM_XPMultiplier.IsReady())
				m_CM_XPMultiplier.Set(cm_RPBase * state);
		}

		virtual void OnDisable() override
		{
			if (m_CM_XPMultiplier.IsReady())
				m_CM_XPMultiplier.Set(cm_RPBase);
		}
	};

	static OverrideRPMultiplier _OverrideCashMultiplier{"overridecashmultiplier", "Override RP Multiplier", "Multiplies RP by the given value"};
	static OverrideRPMultiplier _OverrideRPMultiplier{"overriderpmultiplier", "Override RP Multiplier", "Multiplies RP by the given value"};
	static OverrideRPMultiplier _OverrideContactMissionCashMultiplier{"overridecmcashmultiplier", "Override RP Multiplier", "Multiplies RP by the given value"};
	static OverrideRPMultiplier _OverrideContactMissionRPMultiplier{"overridecmrpmultiplier", "Override RP Multiplier", "Multiplies RP by the given value"};
}