#pragma once

#include "runtime/core/math/transform.h"

#include "runtime/function/physics/physics_actor.h"
#include "runtime/function/physics/ray.h"

namespace Pilot
{
    struct ContactPoint
    {
        Vector3 m_location_a;
        Vector3 m_location_b;
        Vector3 m_normal;
        float   m_penetration;
    };

    struct CollisionInfo
    {
        unsigned int m_id_a;
        unsigned int m_id_b;
        ContactPoint m_contact_point;
        mutable int  m_frame_left;

        void
        addContactPoint(const Vector3& location_a, const Vector3& location_b, const Vector3& normal, float penetration)
        {
            m_contact_point.m_location_a  = location_a;
            m_contact_point.m_location_b  = location_b;
            m_contact_point.m_normal      = normal;
            m_contact_point.m_penetration = penetration;
        }

        bool operator<(const CollisionInfo& other_info) const
        {
            size_t other_hash = (size_t)other_info.m_id_a + ((size_t)other_info.m_id_b << 8);
            size_t this_hash  = (size_t)m_id_a + ((size_t)m_id_b << 8);
            return this_hash < other_hash;
        }

        bool operator==(const CollisionInfo& other_info) const
        {
            if (other_info.m_id_a == m_id_a && other_info.m_id_b == m_id_b)
            {
                return true;
            }

            return false;
        }
    };

    class CollisionDetection
    {
    public:
        CollisionDetection();
        ~CollisionDetection();

        static bool IsOverlap(const Vector3& position_a,
                              const Vector3& position_b,
                              const Vector3& half_dimensions_a,
                              const Vector3& half_dimensions_b);
        static bool ObjectIntersection(PhysicsActor&  object_a,
                                       PhysicsActor&  object_b,
                                       unsigned int   id_a,
                                       unsigned int   id_b,
                                       CollisionInfo& collision_info);

        static Vector3 getClosestPoint(const Vector3& box_size, const Transform& obb_transform, const Vector3& point);

        // intersect functions
        static bool AABBIntersection(const Vector3&   box_a_size,
                                     const Vector3&   box_b_size,
                                     const Transform& world_transform_a,
                                     const Transform& world_transform_b,
                                     CollisionInfo&   collision_info);
        static bool SphereIntersection(const float      sphere_a_radius,
                                       const float      sphere_b_radius,
                                       const Transform& world_transform_a,
                                       const Transform& world_transform_b,
                                       CollisionInfo&   collision_info);
        static bool AABBSphereIntersection(const Vector3&   box_size,
                                           const float      sphere_radius,
                                           const Transform& world_transform_a,
                                           const Transform& world_transform_b,
                                           CollisionInfo&   collision_info);
        static bool OBBIntersection(const Vector3&   box_a_size,
                                    const Vector3&   box_b_size,
                                    const Transform& world_transform_a,
                                    const Transform& world_transform_b,
                                    CollisionInfo&   collision_info);
        static bool OBBSphereIntersection(const Vector3&   box_size,
                                          const float      sphere_radius,
                                          const Transform& world_transform_a,
                                          const Transform& world_transform_b,
                                          CollisionInfo&   collision_info);

        // raycasting functions
        static bool RayIntersection(const Ray& r, PhysicsActor& object_a, RayCollision& collisions);
        static bool
        RayBoxIntersection(const Ray& r, const Vector3& box_pos, const Vector3& box_size, RayCollision& collision);
        static bool RayAABBIntersection(const Ray&       r,
                                        const Transform& world_transform,
                                        const Vector3&   box_size,
                                        RayCollision&    collision);
        static bool RayOBBIntersection(const Ray&       r,
                                       const Transform& world_transform,
                                       const Vector3&   box_size,
                                       RayCollision&    collision);
        static bool RaySphereIntersection(const Ray&       r,
                                          const Transform& world_transform,
                                          const float      sphere_radius,
                                          RayCollision&    collision);
    };
} // namespace Pilot