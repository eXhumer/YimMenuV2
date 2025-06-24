#include "core/commands/LoopedCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	static FloatCommand _CashMultiplierInput{"cashmultiplierinput", "Cash Multiplier Input", "Cash Mulitplier (< 0 = 0 -> No Cash)", std::nullopt, std::nullopt, 1};
	static FloatCommand _RPMultiplierInput{"rpmultiplierinput", "RP Multiplier Input", "RP Mulitplier (< 0 = 0 -> No RP)", std::nullopt, std::nullopt, 1};
	static FloatCommand _CMCashMultiplierInput{"cmcashmultiplierinput", "Contact Mission Cash Multiplier Input", "Contact Mission Cash Mulitplier (< 0 = 0 -> No Mission Cash)", std::nullopt, std::nullopt, 1};
	static FloatCommand _CMRPMultiplierInput{"cmrpmultiplierinput", "Contact Mission RP Multiplier Input", "Contact Mission RP Mulitplier (< 0 = 0 -> No Mission RP)", std::nullopt, std::nullopt, 1};

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
			auto state = _RPMultiplierInput.GetState();
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

		Tunable m_CMCashMultiplier{"CONTACT_MISSION_CASH_BASE_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _CMCashMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CMCashMultiplier.IsReady())
				m_CMCashMultiplier.Set(cm_CashBase * state);
		}

		virtual void OnDisable() override
		{
			if (m_CMCashMultiplier.IsReady())
				m_CMCashMultiplier.Set(cm_CashBase);
		}
	};

	class OverrideCMRPMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_CMXPMultiplier{"CONTACT_MISSION_RP_BASE_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _CMRPMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CMXPMultiplier.IsReady())
				m_CMXPMultiplier.Set(cm_RPBase * state);
		}

		virtual void OnDisable() override
		{
			if (m_CMXPMultiplier.IsReady())
				m_CMXPMultiplier.Set(cm_RPBase);
		}
	};

	static OverrideCashMultiplier _OverrideCashMultiplier{"overridecashmultiplier", "Override Cash Multiplier", "Multiplies Cash by the given value"};
	static OverrideRPMultiplier _OverrideRPMultiplier{"overriderpmultiplier", "Override RP Multiplier", "Multiplies RP by the given value"};
	static OverrideCMCashMultiplier _OverrideCMCashMultiplier{"overridecmcashmultiplier", "Override Contact Mission Cash Multiplier", "Multiplies Mission Cash by the given value"};
	static OverrideCMRPMultiplier _OverrideCMRPMultiplier{"overridecmrpmultiplier", "Override Contact MIssion RP Multiplier", "Multiplies Mission RP by the given value"};
}