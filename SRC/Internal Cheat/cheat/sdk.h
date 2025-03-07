#include "etc.h"

class col {
public:
	float r;
	float g;
	float b;
	float a;
	col(float rr, float gg, float bb, float aa) {
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};

static auto Find = reinterpret_cast<uintptr_t(*)(rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method("Shader", "Find", 1, (char*)"", "UnityEngine")));
static auto SetColor = reinterpret_cast<void(*)(uintptr_t material, rust::classes::string name, col value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method("Material", "SetColor", 2, (char*)"name", "UnityEngine", 1)));
static auto get_material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method("Renderer", "get_material", 0, (char*)"", "UnityEngine")));
static auto get_Renderers = reinterpret_cast<rust::list<uintptr_t>*(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("SkinnedMultiMesh"), ("get_Renderers"), 0, (char*)(""), (""))));

inline void init_bp() {
	Find = reinterpret_cast<uintptr_t(*)(rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method("Shader", "Find", 1, (char*)"", "UnityEngine")));
	SetColor = reinterpret_cast<void(*)(uintptr_t, rust::classes::string name, col value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method("Material", "SetColor", 2, (char*)"name", "UnityEngine", 1)));
	get_Renderers = reinterpret_cast<rust::list<uintptr_t> *(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("SkinnedMultiMesh"), ("get_Renderers"), 0, (char*)(""), (""))));
	get_material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method("Renderer", "get_material", 0, (char*)"", "UnityEngine")));

}