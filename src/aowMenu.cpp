#pragma once

#include "aowMenu.h"
#include "RE/P/PlayerCharacter.h"
#include "RE/A/Actor.h"

aowMenu::aowMenu()
{
	auto scaleformManager = RE::BSScaleformManager::GetSingleton();

	depthPriority = 0;

	menuFlags.set(RE::UI_MENU_FLAGS::kAlwaysOpen);
	menuFlags.set(RE::UI_MENU_FLAGS::kRequiresUpdate);
	menuFlags.set(RE::UI_MENU_FLAGS::kAllowSaving);
	inputContext = Context::kNone;

	if (uiMovie) {
		uiMovie->SetMouseCursorCount(0);
	}

	scaleformManager->LoadMovieEx(this, MENU_PATH, [](RE::GFxMovieDef* a_def) -> void {
		a_def->SetState(RE::GFxState::StateType::kLog,
			RE::make_gptr<Logger>().get());
	});
}

void aowMenu::Register()
{
	logger::info("registering aow");
	auto ui = RE::UI::GetSingleton();
	if (ui) {
		ui->Register(MENU_NAME, Creator);
		logger::info("registered aow");
	} else 
		logger::info("did not register aow");
}

void aowMenu::Show()
{
	logger::info("showing aow");
	auto msgQ = RE::UIMessageQueue::GetSingleton();
	if (msgQ) {
		msgQ->AddMessage(aowMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
		logger::info("showed aow");
		auto ui = RE::UI::GetSingleton();
		if (!ui) {
			logger::info("ui not loaded");
		} else {
			auto overlayMenu = ui->GetMenu(aowMenu::MENU_NAME);
			if (!overlayMenu || !overlayMenu->uiMovie) {
				logger::info("overlaymenu not loaded");
			} else {
				logger::info("menu exists");
				const std::string_view& test = "aowMenu";
				if (ui->IsMenuOpen(test)) {
					logger::info("menu open");
				} else {
					logger::info("menu not open");
				}
			}
		}
		#if false
		SKSE::GetTaskInterface()->AddUITask([]() {
			auto player = RE::PlayerCharacter::GetSingleton();
			if (player) {
				auto power = player->selectedPower;
				if (power) {
					auto text = power->As<RE::SpellItem>()->fullName.c_str();
					const RE::GFxValue newName = text;
					aowMenu::SetName(newName);
					aowMenu::SetLocation(100.0f, 200.0f, 0.0f, 100.0f, 100.0f);
				}
			}
		});
		#endif
	} else
		logger::info("failed to show aow");
}

void aowMenu::Hide()
{
	auto msgQ = RE::UIMessageQueue::GetSingleton();
	if (msgQ) {
		msgQ->AddMessage(aowMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
		logger::warn("hide");
	}
}

void aowMenu::toggleVisibility(bool mode)
{
	logger::warn("trying to change visibility");
	auto ui = RE::UI::GetSingleton();
	if (!ui)
		return;

	auto overlayMenu = ui->GetMenu(aowMenu::MENU_NAME);
	if (!overlayMenu || !overlayMenu->uiMovie)
		return;

	overlayMenu->uiMovie->SetVisible(mode);
	if (mode) {
		logger::warn("visible true");
	} else {
		logger::warn("visible false");
	}
}

// overload to allow you to set name manually
void aowMenu::SetName(RE::GFxValue newName)
{
	RE::GPtr<RE::IMenu> menuObject = RE::UI::GetSingleton()->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set name, but menuObject did not exist.");
		return;
	}
	menuObject->uiMovie->Invoke("ash.setText", nullptr, &newName, 1);
}

// overload to allow you to set location manually
void aowMenu::SetLocation(float xpos, float ypos, float rot, float xscale, float yscale)
{
	RE::GPtr<RE::IMenu> menuObject = RE::UI::GetSingleton()->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set location, but menuObject did not exist.");
		return;
	}
	const RE::GFxValue widget_xpos = xpos;
	const RE::GFxValue widget_ypos = ypos;
	const RE::GFxValue widget_rotation = rot;
	const RE::GFxValue widget_xscale = xscale;
	const RE::GFxValue widget_yscale = yscale;
	RE::GFxValue posArray[5]{ widget_xpos, widget_ypos, widget_rotation, widget_xscale, widget_yscale };
	menuObject->uiMovie->Invoke("ash.setLocation", nullptr, posArray, 5);
}

void aowMenu::SetLocation()
{
#if false
	RE::GPtr<RE::IMenu> menuObject = RE::UI::GetSingleton()->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set location, but menuObject did not exist.");
		return;
	}
	//replace these Settings calls with toml++ calls
	const RE::GFxValue widget_xpos = Settings::GetSingleton()->widget_xpos;
	const RE::GFxValue widget_ypos = Settings::GetSingleton()->widget_ypos;
	const RE::GFxValue widget_rotation = Settings::GetSingleton()->widget_rotation;
	const RE::GFxValue widget_xscale = Settings::GetSingleton()->widget_xscale;
	const RE::GFxValue widget_yscale = Settings::GetSingleton()->widget_yscale;
	RE::GFxValue posArray[5]{ widget_xpos, widget_ypos, widget_rotation, widget_xscale, widget_yscale };
	menuObject->uiMovie->Invoke("ash.setLocation", nullptr, posArray, 5);
#endif
}

void aowMenu::SetName()
{
#if false
	RE::GPtr<RE::IMenu> menuObject = RE::UI::GetSingleton()->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set name, but menuObject did not exist.");
		return;
	}
	RE::GFxValue newName = get name somehow, maybe have it be a static c_str somewhere?
	menuObject->uiMovie->Invoke("ash.setText", nullptr, &newName, 1);
#endif
}

#if false
// dont really need this for aow atm, but might later on if more is added.
void aowMenu::Update()
{

}


// Every time a new frame of the menu is rendered call the update function.
void aowMenu::AdvanceMovie(float a_interval, std::uint32_t a_currentTime)
{
	//aowMenu::Update();
	RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
}

#endif
