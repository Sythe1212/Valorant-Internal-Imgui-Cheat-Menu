#pragma once

#include "etc.h"

#include "rust.h"

namespace unity {
	inline static auto set_lockstate = reinterpret_cast<void(*)(rust::classes::CursorLockMode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Cursor"), ("set_lockState"), 1, (char*)("value"), ("UnityEngine"))));

	inline static auto get_width = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Screen"), ("get_width"), 0, (char*)(""), ("UnityEngine"))));

	inline static auto get_height = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Screen"), ("get_height"), 0, (char*)(""), ("UnityEngine"))));

	inline static auto GetKeyDown = reinterpret_cast<bool(*)(rust::classes::KeyCode key)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Input"), ("GetKeyDown"), 1, (char*)("key"), ("UnityEngine"), 1)));

	inline static auto get_main_camera = reinterpret_cast<uintptr_t(*)()>(il2cpp::methods::resolve_icall(("UnityEngine.Camera::get_main()")));

	inline static auto IgnoreLayerCollision = reinterpret_cast<void(*)(rust::classes::layer, rust::classes::layer, bool)>(il2cpp::methods::resolve_icall(("UnityEngine.Physics::IgnoreLayerCollision()")));

	inline static auto get_keyCode = reinterpret_cast<rust::classes::KeyCode(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Event"), ("get_keyCode"), 0, (char*)(""), ("UnityEngine"))));

	inline static auto LineOfSight = reinterpret_cast<bool(*)(Vector3, Vector3, rust::classes::Layers layer, float padding)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("GamePhysics"), ("LineOfSight"), -1, (char*)(""), (""))));

	inline static auto GetKey = reinterpret_cast<bool(*)(rust::classes::KeyCode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Input"), ("GetKeyInt"), 1, (char*)(""), ("UnityEngine"))));

	inline static auto set_visible = reinterpret_cast<void(*)(bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Cursor"), ("set_visible"), 1, (char*)("value"), ("UnityEngine"))));

	inline static auto get_shader = reinterpret_cast<uintptr_t(*)(uintptr_t material)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Material"), ("get_shader"), 0, (char*)(""), ("UnityEngine"))));

	inline static auto set_shader = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(il2cpp::methods::resolve_icall(("UnityEngine.Material::set_shader()")));

	inline void init_unity() {
		get_shader = reinterpret_cast<uintptr_t(*)(uintptr_t material)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Material"), ("get_shader"), 0, (char*)(""), ("UnityEngine"))));

		set_shader = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(il2cpp::methods::resolve_icall(("UnityEngine.Material::set_shader()")));

		set_lockstate = reinterpret_cast<void(*)(rust::classes::CursorLockMode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Cursor"), ("set_lockState"), 1, (char*)("value"), ("UnityEngine"))));

		set_visible = reinterpret_cast<void(*)(bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Cursor"), ("set_visible"), 1, (char*)("value"), ("UnityEngine"))));

		get_width = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Screen"), ("get_width"), 0, (char*)(""), ("UnityEngine"))));

		get_height = reinterpret_cast<int (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Screen"), ("get_height"), 0, (char*)(""), ("UnityEngine"))));

		GetKeyDown = reinterpret_cast<bool(*)(rust::classes::KeyCode key)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Input"), ("GetKeyDown"), 1, (char*)("key"), ("UnityEngine"), 1)));

		get_main_camera = reinterpret_cast<uintptr_t(*)()>(il2cpp::methods::resolve_icall(("UnityEngine.Camera::get_main()")));

		IgnoreLayerCollision = reinterpret_cast<void(*)(rust::classes::layer, rust::classes::layer, bool)>(il2cpp::methods::resolve_icall(("UnityEngine.Physics::IgnoreLayerCollision()")));

		get_keyCode = reinterpret_cast<rust::classes::KeyCode(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Event"), ("get_keyCode"), 0, (char*)(""), ("UnityEngine"))));

		LineOfSight = reinterpret_cast<bool(*)(Vector3, Vector3, rust::classes::Layers layer, float padding)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("GamePhysics"), ("LineOfSight"), -1, (char*)(""), (""))));

		GetKey = reinterpret_cast<bool(*)(rust::classes::KeyCode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Input"), ("GetKeyInt"), 1, (char*)(""), ("UnityEngine"))));
	}

	inline bool is_visible(Vector3 source, Vector3 destination) {
		auto layer = (int)rust::classes::Layers::ProjectileLineOfSightCheck | (int)rust::classes::Layers::Terrain;

		return LineOfSight(source, destination, rust::classes::Layers(layer), 0);
	}

	inline auto camera = unity::get_main_camera();

	inline VMatrix get_view_matrix() {
		if (!camera) {
			camera = unity::get_main_camera();
		}

		auto camera_ = readnew<uintptr_t>(camera + 0x10);
		if (!camera_) {
			camera = unity::get_main_camera();
			return {};
		}

		auto matrix = readnew<VMatrix>(camera_ + 0x2E4);
		if (!matrix.m) {
			camera = unity::get_main_camera();
			return {};
		}

		return matrix;
	}

	inline Vector3 get_camera_pos() {
		if (!camera) {
			camera = unity::get_main_camera();
		}

		auto camera_ = readnew<uintptr_t>(camera + 0x10);
		if (!camera_) {
			camera = unity::get_main_camera();
			return {};
		}

		auto matrix = readnew<Vector3>(camera_ + 0x42C);
		if (!matrix.x || !matrix.y) {
			camera = unity::get_main_camera();
			return {};
		}


		return matrix;
	}
	inline float get_fov(Vector3 Pos);
}