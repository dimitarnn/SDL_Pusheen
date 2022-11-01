#include <iostream>
#include <SDL.h>
#include "mygraphics.h"
#include <cmath>

const double STEP = 0.001;
const double RATIO = 1.7;

void draw_circle(double x, double y, double r)
{
	for (double i = 0; i < 2 * M_PI; i += STEP)
	{
		drawPixel(x + r * std::cos(i), y - r * std::sin(i));
	}
}

void draw_circle_part(double x, double y, double r, double from, double to)
{
	if (from > to)
	{
		double tmp = from;
		from = to;
		to = tmp;
	}

	for (double i = from; i < to; i += STEP)
	{
		drawPixel(x + r * std::cos(i), y - r * std::sin(i));
	}
}

void draw_line(double x1, double y1, double x2, double y2)
{
	/// (x - x1) / (x2 - x1) = (y - y1) / (y2 - y1)
	/// x * (y2 - y1) - x1 * (y2 - y1) = y * (x2 - x1) - y1 * (x2 - x1)
	/// y = [x * (y2 - y1) - x1 * (y2 - y1) + y1 * (x2 - x1)] / (x2 - x1)

	if (x1 > x2)
	{
		double tmp = x2;
		x2 = x1;
		x1 = tmp;

		tmp = y2;
		y2 = y1;
		y1 = tmp;
	}

	for (double x = x1; x <= x2; x += STEP)
	{
		double y = (x * (y2 - y1) - x1 * (y2 - y1) + y1 * (x2 - x1)) / (x2 - x1);
		drawPixel(x, y);
	}
}

void fill_circle(double x, double y, double r)
{
	for (double dist = 0; dist <= r; dist += 1)
		for (double i = 0; i <= 2 * M_PI; i += STEP)
		{
			drawPixel(x + dist * std::cos(i), y - dist * std::sin(i));
		}
}

int main(int, char**)
{
	double last_x, last_y;

	setColor(255, 255, 255);

	// back lower half
	draw_circle_part(RATIO * 250 + RATIO * 130 * 1.22, RATIO * 250, RATIO * 130 * 2.22, M_PI - (M_PI / 2) * 0.035, M_PI + (M_PI / 2) * 0.28);

	// back upper half
	draw_circle_part(RATIO * 250, RATIO * 250, RATIO * 130, M_PI - (M_PI / 2) * 0.077, (M_PI / 2) * 1.05);
	const double lower_back_x = RATIO * 250 - RATIO * 130;
	const double lower_back_y = RATIO * 250;

	last_x = RATIO * 250 + RATIO * 130 * std::cos((M_PI / 2) * 1.05);
	last_y = RATIO * 250 - RATIO * 130 * std::sin((M_PI / 2) * 1.05);

	const double top_torso_offset = RATIO * 50;

	double const top_torso_x1 = last_x;
	double const top_torso_y1 = last_y;
	double const top_torso_x2 = last_x + RATIO * 130 * 0.9 + top_torso_offset;
	double const top_torso_y2 = last_y;

	// top torso line
	drawLine(top_torso_x1, top_torso_y1, top_torso_x2, top_torso_y2);
	last_x = top_torso_x2;

	// left ear first half
	drawLine(last_x, last_y, last_x + RATIO * 30, last_y - RATIO * 40);
	last_x += RATIO * 30;
	last_y -= RATIO * 40;
	const double left_ear_middle_x = last_x;

	// left ear second half
	drawLine(last_x, last_y, last_x + RATIO * 30, last_y + RATIO * 40);
	last_x += RATIO * 30;
	last_y += RATIO * 40;

	

	// gap between ears
	const double ear_gap_x1 = last_x;
	const double ear_gap_y1 = last_y;
	drawLine(last_x, last_y, last_x + RATIO * 30 * 2.43, last_y);
	last_x += RATIO * 30 * 2.43;

	// right ear first half
	const double ear_gap_x2 = last_x;
	const double ear_gap_y2 = last_y;
	drawLine(last_x, last_y, last_x + RATIO * 30, last_y - RATIO * 40);
	last_x += RATIO * 30;
	last_y -= RATIO * 40;

	// right ear second half
	drawLine(last_x, last_y, last_x + RATIO * 30, last_y + RATIO * 40);
	last_x += RATIO * 30;
	last_y += RATIO * 40;

	// front lower half
	draw_circle_part(RATIO * 350 + RATIO * 130 * 0.47 + top_torso_offset,
		RATIO * 250 + RATIO * 130 * 1.3333 * 0.01,
		RATIO * 130 * 1.3333,
		(M_PI / 2) / 24,
		-1 * (M_PI / 2) * 0.497);

	const double x2 = RATIO * 350 + RATIO * 130 * 0.47;
	const double y2 = RATIO * 250 + RATIO * 130 * 1.3333 * 0.01;
	const double r2 = RATIO * 130 * 1.3333;

	// front upper half
	draw_circle_part(RATIO * 350 + RATIO * 65 - RATIO * 130 * 1.4 * 0.065 + top_torso_offset,
		RATIO * 250 - RATIO * 130 * 1.4 * 0.12,
		RATIO * 130 * 1.4,
		(M_PI / 2) * 0.1,
		(M_PI / 2) * 0.41);
	const double x1 = RATIO * 350 + RATIO * 65 - RATIO * 130 * 1.4 * 0.07;
	const double y1 = RATIO * 250 - RATIO * 130 * 1.4 * 0.12;
	const double r1 = RATIO * 130 * 1.4;


	// connect front lower half to front upper half
	draw_line(x1 + r1 * std::cos((M_PI / 2) * 0.1) + top_torso_offset + STEP * 750,
		y1 - r1 * std::sin((M_PI / 2) * 0.1),
		x2 + r2 * std::cos((M_PI / 2) / 24) + top_torso_offset + STEP * 750,
		y2 - r2 * std::sin((M_PI / 2) / 24));

	const double lower_body_line_x2 = x2 + r2 * std::cos(-1 * (M_PI / 2) * 0.5) + top_torso_offset;
	const double lower_body_line_y2 = y2 - r2 * std::sin(-1 * (M_PI / 2) * 0.5);
	const double lower_body_line_x1 = x2 + r2 * std::cos(-1 * (M_PI / 2) * 0.5) - RATIO * 387;
	const double lower_body_line_y1 = y2 - r2 * std::sin(-1 * (M_PI / 2) * 0.5);

	// torso between back paws
	const double paw_radius = RATIO * 15;

	draw_line(lower_body_line_x1 + paw_radius * 2,
		lower_body_line_y1,
		lower_body_line_x1 + paw_radius * 2 * 4,
		lower_body_line_y1);

	// torso between front and back paws
	draw_line(lower_body_line_x1 + paw_radius * 2 * 5,
		lower_body_line_y1,
		lower_body_line_x2 - paw_radius * 2 * 5,
		lower_body_line_y1);

	// torso between front paws
	draw_line(lower_body_line_x2 - paw_radius * 2,
		lower_body_line_y2,
		lower_body_line_x2 - paw_radius * 2 * 4,
		lower_body_line_y2);

	// leftmost paw
	draw_circle_part(lower_body_line_x1 + paw_radius,
		lower_body_line_y1,
		paw_radius,
		M_PI - 0.075 * (M_PI / 2),
		2 * M_PI);

	// second leftmost paw
	const double paw_distance = paw_radius * 2 * 4;
	draw_circle_part(lower_body_line_x1 + paw_radius + paw_distance,
		lower_body_line_y1,
		paw_radius,
		M_PI,
		2 * M_PI);

	// rightmost paw
	draw_circle_part(lower_body_line_x2 - paw_radius,
		lower_body_line_y2,
		paw_radius,
		M_PI,
		2 * M_PI + 0.03 * (M_PI / 2));

	// second rightmost paw
	draw_circle_part(lower_body_line_x2 - paw_radius - paw_distance,
		lower_body_line_y2,
		paw_radius,
		M_PI,
		2 * M_PI);
	
	// left spot
	double spot_radius = RATIO * 25;
	draw_circle_part(top_torso_x1, top_torso_y1, spot_radius, M_PI + (M_PI / 2) * 0.15, 2 * M_PI);

	// right spot
	double spot_distance = spot_radius * 1.2;
	draw_circle_part(top_torso_x1 + 2 * spot_radius + spot_distance,
		top_torso_y1,
		spot_radius,
		M_PI,
		2 * M_PI);

	const double right_spot_end = top_torso_x1 + 2 * spot_radius + spot_distance + spot_radius * std::cos(2 * M_PI);

	// spots between the ears
	double small_spot_radius = RATIO * 7.5;
	draw_circle_part(ear_gap_x1 + 1.8 * small_spot_radius,
		ear_gap_y1,
		small_spot_radius,
		M_PI,
		2 * M_PI);

	draw_circle_part(ear_gap_x1 + (1.8 + 1 + 2.2) * small_spot_radius,
		ear_gap_y1,
		small_spot_radius,
		M_PI,
		2 * M_PI);

	draw_circle_part(ear_gap_x1 + (1.8 + 2 + 2 * 2.2) * small_spot_radius,
		ear_gap_y1,
		small_spot_radius,
		M_PI,
		2 * M_PI);

	// left eye
	const double eyeline_y = 170 * RATIO;
	const double eye_radius = RATIO * 12;

	fill_circle(left_ear_middle_x + eye_radius * 0.75,
		eyeline_y,
		eye_radius);

	// right eye
	fill_circle(left_ear_middle_x + (0.75 + 2 + 3.5 * 2) * eye_radius,
		eyeline_y,
		eye_radius);

	// nose line
	drawLine(left_ear_middle_x + (0.75 + 1 + 3.5) * eye_radius,
		eyeline_y - eye_radius * 0.5,
		left_ear_middle_x + (0.75 + 1 + 3.5) * eye_radius,
		eyeline_y + 1.25 * eye_radius);

	const double nose_line_bottom_x = left_ear_middle_x + (0.75 + 1 + 3.5) * eye_radius;
	const double nose_line_bottom_y = eyeline_y + 1.25 * eye_radius;

	// left smile part
	const double smile_radius = RATIO * 20;
	draw_circle_part(nose_line_bottom_x - smile_radius / 1.35,
		nose_line_bottom_y - smile_radius / 1.5,
		smile_radius,
		1.75 * M_PI,
		1.5 * M_PI);

	// right smile part
	draw_circle_part(nose_line_bottom_x + smile_radius / 1.35,
		nose_line_bottom_y - smile_radius / 1.5,
		smile_radius,
		1.5 * M_PI,
		1.25 * M_PI);

	// left upper whisker
	const double upper_whisker_length = 45 * RATIO;
	const double left_upper_whisker_x1 = right_spot_end + upper_whisker_length / 4;
	const double left_upper_whisker_y1 = top_torso_y1 + spot_radius * 1.2;

	const double left_upper_whisker_x2 = left_upper_whisker_x1 + upper_whisker_length * std::cos(M_PI / 20);
	const double left_upper_whisker_y2 = left_upper_whisker_y1 + upper_whisker_length * std::sin(M_PI / 20);

	draw_line(left_upper_whisker_x1,
		left_upper_whisker_y1,
		left_upper_whisker_x2,
		left_upper_whisker_y2);

	// left lower whisker
	
	const double lower_whisker_length = 0.95 * upper_whisker_length;
	const double left_lower_whisker_x2 = left_upper_whisker_x2;
	const double left_lower_whisker_y2 = left_upper_whisker_y2 + eye_radius * 1.2;

	const double left_lower_whisker_x1 = left_lower_whisker_x2 - lower_whisker_length * std::cos(M_PI / 45);
	const double left_lower_whisker_y1 = left_lower_whisker_y2 + lower_whisker_length * std::sin(M_PI / 45);

	draw_line(left_lower_whisker_x2,
		left_lower_whisker_y2,
		left_lower_whisker_x1,
		left_lower_whisker_y1);

	// right upper whisker

	draw_line(left_upper_whisker_x2 + 265 * RATIO,
		left_upper_whisker_y1,
		left_upper_whisker_x1 + 265 * RATIO,
		left_upper_whisker_y2);

	// right lower whisker

	const double right_lower_whisker_x2 = left_lower_whisker_x2 + 270 * RATIO;
	const double right_lower_whisker_x1 = right_lower_whisker_x2 - lower_whisker_length * std::cos(M_PI / 45);
	const double right_lower_whisker_y2 = left_lower_whisker_y1;
	const double right_lower_whisker_y1 = right_lower_whisker_y2 + lower_whisker_length * std::sin(M_PI / 45);

	draw_line(right_lower_whisker_x1,
		right_lower_whisker_y1,
		right_lower_whisker_x2,
		right_lower_whisker_y2);

	// draw tail upper half
	const double tail_part_radius = 100 * RATIO;
	
	draw_circle_part(lower_back_x - tail_part_radius * 0.26,
		lower_back_y + tail_part_radius * 0.21,
		tail_part_radius,
		(M_PI / 2) + (M_PI / 2) * 0.075,
		(M_PI / 2) * 0.7);

	// draw tail lower half
	draw_circle_part(lower_back_x - tail_part_radius * 0.5 + 0.775 * tail_part_radius,
		lower_back_y - tail_part_radius,
		tail_part_radius,
		(M_PI / 2) * 3 - (M_PI / 2) * 0.18,
		M_PI + (M_PI / 2) * 0.4);

	// draw tail top

	const double tail_fluff_radius = 24 * RATIO;
	draw_circle_part(lower_back_x - tail_fluff_radius * 1.38,
		lower_back_y - 2.29 * tail_fluff_radius,
		tail_fluff_radius,
		(M_PI / 2),
		(M_PI) + (M_PI / 2) * 0.4);
	
	// color tail
	const double stripe_distance = 20 * RATIO;
	const double stripe_radius = 2 * tail_fluff_radius;
	const double stripe_x = lower_back_x - tail_fluff_radius * 1.75 + stripe_distance * stripe_radius / tail_fluff_radius;
	const double stripe_y = lower_back_y - 2.29 * tail_fluff_radius + 0.75 * stripe_distance;

	// color first stripe
	for (double i = stripe_x,
		start_angle = (M_PI / 2) * 0.4,
		end_angle = (M_PI / 2) * 0.05,
		j = stripe_y;
		i <= stripe_x + 0.3 * stripe_distance * stripe_radius / tail_fluff_radius &&
		j <= stripe_y + 0.3 * 0.75 * stripe_distance;
		++i,
		++j,
		start_angle *= 0.956,
		end_angle *= 1.01)
		draw_circle_part(i, j, stripe_radius, (M_PI / 2) + start_angle, (M_PI) + end_angle);

	// color second stripe
	const double stripe_x1 = stripe_x + 0.45 * stripe_distance * stripe_radius / tail_fluff_radius;
	const double stripe_y1 = stripe_y + 0.45 * 0.75 * stripe_distance;
	for (double i = stripe_x1,
		start_angle = (M_PI / 2) * 0.4 * 0.7,
		end_angle = (M_PI / 2) * 0.075 * 3,
		j = stripe_y1;
		i <= stripe_x1 + 0.43 * stripe_distance * stripe_radius / tail_fluff_radius &&
		j <= stripe_y1 + 0.5 * 0.75 * stripe_distance;
		++i,
		++j,
		start_angle *= 0.965,
		end_angle *= 0.975)
		draw_circle_part(i, j, stripe_radius, (M_PI / 2) + start_angle, (M_PI) + end_angle);

	updateGraphics();
	std::cin.get();

	SDLEnd();
	return 0;
}