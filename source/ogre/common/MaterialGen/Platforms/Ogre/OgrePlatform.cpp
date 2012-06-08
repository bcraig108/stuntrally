#include "OgrePlatform.hpp"

#include "OgreMaterial.hpp"
#include "OgreVertexProgram.hpp"
#include "OgreFragmentProgram.hpp"
#include "OgreGeometryProgram.hpp"

namespace
{
	std::string convertLang (sh::Language lang)
	{
		if (lang == sh::Language_CG)
			return "cg";
		else if (lang == sh::Language_HLSL)
			return "hlsl";
		else if (lang == sh::Language_GLSL)
			return "glsl";
	}
}

namespace sh
{
	OgrePlatform::OgrePlatform(const std::string& resourceGroupName)
		: Platform()
		, mResourceGroup(resourceGroupName)
	{
		Ogre::MaterialManager::getSingleton().addListener(this);
	}

	OgrePlatform::~OgrePlatform ()
	{
	}

	bool OgrePlatform::supportsMaterialQueuedListener ()
	{
		return true;
	}

	boost::shared_ptr<Material> OgrePlatform::createMaterial (const std::string& name)
	{
		OgreMaterial* material = new OgreMaterial(name, mResourceGroup);
		return boost::shared_ptr<Material> (material);
	}

	boost::shared_ptr<VertexProgram> OgrePlatform::createVertexProgram (
		const std::string& name, const std::string& entryPoint,
		const std::string& source, Language lang)
	{
		OgreVertexProgram* prog = new OgreVertexProgram (name, entryPoint, source, convertLang(lang), mResourceGroup);
		return boost::shared_ptr<VertexProgram> (prog);
	}

	boost::shared_ptr<FragmentProgram> OgrePlatform::createFragmentProgram (
		const std::string& name, const std::string& entryPoint,
		const std::string& source, Language lang)
	{
		OgreFragmentProgram* prog = new OgreFragmentProgram (name, entryPoint, source, convertLang(lang), mResourceGroup);
		return boost::shared_ptr<FragmentProgram> (prog);
	}

	boost::shared_ptr<GeometryProgram> OgrePlatform::createGeometryProgram (
		const std::string& name, const std::string& entryPoint,
		const std::string& source, Language lang)
	{
		OgreGeometryProgram* prog = new OgreGeometryProgram (name, entryPoint, source, convertLang(lang), mResourceGroup);
		return boost::shared_ptr<GeometryProgram> (prog);
	}

	Ogre::Technique* OgrePlatform::handleSchemeNotFound (
		unsigned short schemeIndex, const Ogre::String &schemeName, Ogre::Material *originalMaterial,
		unsigned short lodIndex, const Ogre::Renderable *rend)
	{
		fireMaterialRequested(originalMaterial->getName());
		return originalMaterial->createTechnique(); /// \todo
	}
}