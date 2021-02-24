#pragma once

#include <memory>
#include <string>
#include <map>

namespace Resources
{

/**
 * A template class for handling SFML resources, such as textures, sound effects and music themes.
 * The user of the class can load/open resources from files,
 * and then retrieve them through the class and use them.
 * 
 * @param[in] ResourceIdType
 *  The type of the resource IDs that will be used to specify resources
 *  when loading/opening or retrieving resources
 * @param[in] ResourceType
 *  The type of the resources themselves
 * @param[in] LoadOrOpen
 *  Specifies whether the resource handler will load whole resources on the GPU,
 *  or it will open them for streaming.
 *  Setting this parameter to true will make the handler load resources,
 *  and setting it to false will make it open resources.
 *  By default resource handlers load resources,
 *  so that parameter is set to true by default.
 */
template <class ResourceIdType, class ResourceType, bool LoadOrOpen = true>
class ResourceHandler;

template <class ResourceIdType, class ResourceType>
class ResourceHandler
<ResourceIdType, ResourceType, true>
{
  
  public:

    /**
     * Loads a resource for the given ID from the given file.
     * 
     * @param[in] id
     *  Id of the resource that we want to load
     * @param[in] filename
     *  Name of the file where the resource is located
     */
    void Load(
        ResourceIdType id,
        std::string const& filename
    );

    /**
     * Returns a reference to the resource with the requested Id.
     * Note that the resource at that Id should be loaded first.
     * 
     * @param[in] id
     *  Id of the resource that we want to retrieve
     * 
     * @return reference to the requested resource
     */
    ResourceType& Get(ResourceIdType id);
    ResourceType const& Get(ResourceIdType id) const;

  private:

    /// Map of the resources. Maps each resource Id with the corresponding resource object
    std::map<
      ResourceIdType,
      std::unique_ptr<ResourceType>
    > _resourceMap;
};

template <class ResourceIdType, class ResourceType>
class ResourceHandler
<ResourceIdType, ResourceType, false>
{
  
  public:

    /**
     * Opens a resource for the given ID from the given file.
     * 
     * @param[in] id
     *  Id of the resource that we want to open
     * @param[in] filename
     *  Name of the file where the resource is located
     */
    void Open(
        ResourceIdType id,
        std::string const& filename
    );

    /**
     * Returns a reference to the resource with the requested Id.
     * Note that the resource at that Id should be opened first.
     * 
     * @param[in] id
     *  Id of the resource that we want to retrieve
     * 
     * @return reference to the requested resource
     */
    ResourceType& Get(ResourceIdType id);
    ResourceType const& Get(ResourceIdType id) const;

  private:

    /// Map of the resources. Maps each resource Id with the corresponding resource object
    std::map<
      ResourceIdType,
      std::unique_ptr<ResourceType>
    > _resourceMap;
};

// RIDT = ResourceIdType, RT = ResourceType
template <class RIDT, class RT>
void ResourceHandler<RIDT, RT, true>::Load(
    RIDT id,
    std::string const& filename)
{
    std::unique_ptr<RT> resource = std::make_unique<RT>();
    if (!resource->loadFromFile(filename))
    {
        throw "Error: Cannot load resource from file: " + filename;
    }
    
    _resourceMap.insert(std::make_pair(id, std::move(resource)));
}

// RIDT = ResourceIdType, RT = ResourceType
template <class RIDT, class RT>
void ResourceHandler<RIDT, RT, false>::Open(
    RIDT id,
    std::string const& filename)
{
    std::unique_ptr<RT> resource = std::make_unique<RT>();
    if (!resource->openFromFile(filename))
    {
        throw "Error: Cannot open resource from file: " + filename;
    }
    
    _resourceMap.insert(std::make_pair(id, std::move(resource)));
}

// The following 4 method definitions are all the same so I use this macro
#define GET_METHOD_DEFINITION \
auto found = _resourceMap.find(id); \
if (found == _resourceMap.end()) \
{ \
    throw "Error: No resource loaded/opened for the requested resource ID"; \
} \
return *(found->second);

// RIDT = ResourceIdType, RT = ResourceType
template <class RIDT, class RT>
RT& ResourceHandler<RIDT, RT, true>::Get(RIDT id)
{ GET_METHOD_DEFINITION; }
template <class RIDT, class RT>
RT const& ResourceHandler<RIDT, RT, true>::Get(RIDT id) const
{ GET_METHOD_DEFINITION; }
template <class RIDT, class RT>
RT& ResourceHandler<RIDT, RT, false>::Get(RIDT id)
{ GET_METHOD_DEFINITION; }
template <class RIDT, class RT>
RT const& ResourceHandler<RIDT, RT, false>::Get(RIDT id) const
{ GET_METHOD_DEFINITION; }

// Undefining the macro, so that it doesn't create confusion in other files
#undef GET_METHOD_DEFINITION

} // namespace Resources