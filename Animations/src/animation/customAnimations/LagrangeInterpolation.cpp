#include "animation/customAnimations/LagrangeInterpolation.h"
#include "animation/Animation.h"
#include "animation/AnimationBuilders.h"
#include "animation/Styles.h"

namespace MathAnim
{
	namespace LagrangeInterpolation
	{
        // Adapted from https://www.geeksforgeeks.org/lagranges-interpolation/
		static float lagrange(std::initializer_list<Vec2> points, float xi)
		{
            float result = 0; // Initialize result

            for (const Vec2& p0 : points)
            {
                // Compute individual terms of above formula
                float term = p0.y;
                for (const Vec2& p1 : points)
                {
                    if (&p0 != &p1)
                        term *= (xi - p1.x) / (p0.x - p1.x);
                }

                // Add current term to result
                result += term;
            }

            return result;
		}

        static void drawLagrangeInterpolation3D(std::initializer_list<Vec2> points, float xStart, float xEnd, int granularity, float duration)
        {
			Style pointStyle = Styles::defaultStyle;
			pointStyle.color = Colors::blue;

			for (const Vec2& point : points)
			{
				AnimationManager::addAnimation(
					FilledCircleAnimationBuilder()
					.setPosition(point)
					.setRadius(0.06f)
					.setDuration(0.16f)
					.setNumSegments(40)
					.build(),
					pointStyle
				);
			}

			Style lineStyle = Styles::defaultStyle;
			lineStyle.color = Colors::offWhite;

			float lineSegmentLength = (xEnd - xStart) / (float)granularity;
			float eachDuration = duration / (float)granularity;
			Vec2 pos = {
				xStart,
				lagrange(points, xStart)
			};
			for (int i = 0; i < granularity; i++)
			{
				Vec2 nextPos = pos + Vec2{pos.x + lineSegmentLength, lagrange(points, pos.x + lineSegmentLength)};
				AnimationManager::addAnimation(
					Bezier1AnimationBuilder()
					.setP0(pos)
					.setP1(nextPos)
					.setDuration(eachDuration)
					.build(),
					lineStyle
				);

				pos.x += lineSegmentLength;
				pos.y = lagrange(points, pos.x);
			}
        }

		static void drawLagrangeInterpolation(std::initializer_list<Vec2> points, float xStart, float xEnd, int granularity, float duration)
		{
			Style pointStyle = Styles::defaultStyle;
			pointStyle.color = Colors::blue;

			for (const Vec2& point : points)
			{
				AnimationManager::addAnimation(
					FilledCircleAnimationBuilder()
					.setPosition(point)
					.setRadius(0.06f)
					.setDuration(0.16f)
					.setNumSegments(40)
					.build(),
					pointStyle
				);
			}

			Style lineStyle = Styles::defaultStyle;
			lineStyle.color = Colors::offWhite;

			float lineSegmentLength = (xEnd - xStart) / (float)granularity;
			float eachDuration = duration / (float)granularity;
			Vec2 pos = {
				xStart,
				lagrange(points, xStart)
			};
			for (int i = 0; i < granularity; i++)
			{
				Vec2 nextPos = Vec2{pos.x + lineSegmentLength, lagrange(points, pos.x + lineSegmentLength)};
				AnimationManager::addAnimation(
					Bezier1AnimationBuilder()
					.setP0(pos)
					.setP1(nextPos)
					.setDuration(eachDuration)
					.build(),
					lineStyle
				);

				pos = nextPos;
			}
		}

		void init()
		{
			Vec2 p00{-4.0f, -0.25f};
			Vec2 p0{-3.0f, 0.0f};
			Vec2 p1{-1.5f, 0.5f};
			Vec2 p2{0.0f, -0.0f};
			Vec2 p3{1.5f, 0.5f};
			Vec2 p4{3.0f, 0.0f};
			Vec2 p5{4.0f, 0.25f};

			drawLagrangeInterpolation(
				{ p00, p0, p1, p2, p3, p4, p5 },
				-4.0f, 4.0f, 100, 5.0f);

			Style orange = Styles::defaultStyle;
			orange.color = Colors::orange;
			AnimationManager::addAnimation(
				Bezier1AnimationBuilder()
				.setP0(p00)
				.setP1(p0)
				.setDuration(1.0f)
				.setDelay(3.5f)
				.build(),
				orange
			);
		}
	}
}
