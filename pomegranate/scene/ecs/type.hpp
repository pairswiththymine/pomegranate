#pragma once

#include "base.hpp"

#include <utility>

#include "component.hpp"
#include "util/misc.hpp"

namespace pom {
    /// @addtogroup ecs
    /// @{

    /// Entities have types represented by a constant array of `ComponentMetadata`. components are unique within a type
    /// and sorted based on their id which is arbitrary.
    class Type {
    public:
        Type() = default;

        /// Constructs a Type from a template parameter pack of Components. The passed components must be unique.
        template <Component... Cs> requires(are_distinct<Cs...>) [[nodiscard]] static Type fromPack()
        {
            // TODO: compile time sorting
            POM_PROFILE_FUNCTION();
            Type t;
            t.components = { getComponentMetadata<Cs>()... };
            t.sort();
            return t;
        }

        [[nodiscard]] inline Type add(const ComponentMetadata& added) const
        {
            POM_PROFILE_FUNCTION();
            Type newType = { components };
            if (newType.indexOf(added.id) == -1) {
                newType.components.push_back(added);
                newType.sort();
            }
            return newType;
        }

        /// Creates a new type from a type having added a component. If the existing type already contains the
        /// component, it returns the same type.
        template <Component C> [[nodiscard]] Type add() const
        {
            POM_PROFILE_FUNCTION();
            return add(getComponentMetadata<C>());
        }

        /// Creates a new type from a type having removed a component. If the existing type does not contain the
        /// component, it returns the same type.
        [[nodiscard]] inline Type remove(const ComponentMetadata& metatadata) const
        {
            POM_PROFILE_FUNCTION();
            Type newType = { components };
            auto it = binaryFind(newType.components.begin(), newType.components.end(), metatadata);
            if (it != newType.components.end())
                newType.components.erase(it);
            return newType;
        }

        /// Creates a new type from a type having removed a component. If the existing type does not contain the
        /// component, it returns the same type.
        template <Component C> [[nodiscard]] Type remove() const
        {
            return remove(getComponentMetadata<C>());
        }

        /// Returns the index of a component within the type, if the component does not exist returns -1.
        [[nodiscard]] inline i32 indexOf(ComponentId id) const
        {
            POM_PROFILE_FUNCTION();
            auto it = binaryFind(components.cbegin(),
                                 components.cend(),
                                 ComponentMetadata { .id = id },
                                 [](const ComponentMetadata& a, const ComponentMetadata& b) { return a.id < b.id; });
            if (it == components.cend())
                return -1;

            return it - components.cbegin();
        }

        /// Returns the index of a component within the type, if the component does not exist returns -1.
        template <Component C> [[nodiscard]] inline i32 indexOf() const
        {
            POM_PROFILE_FUNCTION();
            return indexOf(componentId<C>());
        }

        /// Returns true if the type contains the component, false otherwise.
        template <Component C> [[nodiscard]] inline bool contains() const
        {
            POM_PROFILE_FUNCTION();

            return indexOf<C>() != -1;
        }

        /// Returns true if the type contains the component, false otherwise.
        [[nodiscard]] inline bool contains(ComponentId c) const
        {
            POM_PROFILE_FUNCTION();

            return indexOf(c) != -1;
        }

        /// Returns the number of components within the type.
        [[nodiscard]] usize size() const
        {
            return components.size();
        }

        [[nodiscard]] const ComponentMetadata& operator[](usize idx) const
        {
            return components[idx];
        }

        /// Returns true if the passed parameter pack could be used to construct this type.
        template <Component... Cs>
        requires(are_distinct<Cs...>) [[nodiscard]] bool is() const
        {
            // TODO: compile time sorting
            // NOTE: this assumes Cs... is sorted
            POM_PROFILE_FUNCTION();
            return ((components[TupleIndex<Cs, std::tuple<Cs...>>::value].id == componentId<Cs>)&&...);
        }

        template <Component... Cs> requires(are_distinct<Cs...>) [[nodiscard]] bool match() const
        {
            POM_PROFILE_FUNCTION();

            return (contains<Cs>() + ...) == std::tuple_size<std::tuple<Cs...>>::value;
        }

        [[nodiscard]] auto begin() const
        {
            return components.cbegin();
        }

        [[nodiscard]] auto end() const
        {
            return components.cend();
        }

    private:
        friend std::ostream& operator<<(std::ostream& os, const Type& type);

        Type(std::vector<ComponentMetadata> data) : components(std::move(data))
        {
        }

        void sort()
        {
            POM_PROFILE_FUNCTION();

            std::sort(components.begin(), components.end(), [](ComponentMetadata& a, ComponentMetadata& b) {
                return a.id < b.id;
            });
        }

        std::vector<ComponentMetadata> components;
    };

    /// @}

    inline std::ostream& operator<<(std::ostream& os, const Type& type)
    {
        if (type.components.empty()) {
            os << "NullType []";
        } else {
            os << "Type [ ";
            for (usize i = 0; i < type.size() - 1; i++)
                os << type[i].name << ", ";
            os << type.components.back().name << " ]";
        }
        return os;
    }
} // namespace pom