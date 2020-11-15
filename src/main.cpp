#include "RingBuffer.h"
#include "mathlib.hpp"
#include "stdint.h"

struct sample {
	uint64_t time_us;
	float data[3];
};

#include <cmath>
#define ISFINITE(x) __builtin_isfinite(x)

int main()
{
	float num1 = 10.0f;
	float num2 = 20.0f;
	float num3 = 0.0f;

	num3 = math::constrain(num1, -5.0f, 5.0f);

	printf("%f\n", num3);

	return 0;
}


/*
int main()
{
	float gyro = NAN;
	bool is_true = ISFINITE(gyro);
	printf("is_true: %d\n", is_true);


	Eulerf eul(0.1,0.2,0);
	Quatf q1(eul);
	Quatf q2;
	Quatf q_error =  q2 * q1;
	q_error.normalize();
	printf("q_error: [%f, %f, %f, %f]\n", q_error(0),q_error(1),q_error(2),q_error(3));

	AxisAnglef delta_ang_error1(q_error);
	printf("delta_ang_error1: [%f, %f, %f]\n", delta_ang_error1(0),delta_ang_error1(1),delta_ang_error1(2));

	// 计算姿态跟踪误差
	float scalar = 2.0f;//(q_error(0) < 0.0f) ? 2.0f: -2.0f;	
	const Vector3f delta_ang_error2{scalar * q_error(1), scalar * q_error(2), scalar * q_error(3)};	
	printf("delta_ang_error2: [%f, %f, %f]\n", delta_ang_error2(0),delta_ang_error2(1),delta_ang_error2(2));

	return 1;

}
/*
int main()
{
	RingBuffer<sample> buffer;
	if (buffer.allocate(3)) {
		printf("succeed\n");
	};

	
	for (int i = 0; i < 1; ++i) {
		sample t1;
		t1.time_us = 1000 * i;
		t1.data[0] = 0 + i * 3;
		t1.data[1] = 1 + i * 3;
		t1.data[2] = 2 + i * 3;
		buffer.push(t1);
	}

	printf("tail: %d\n", buffer.get_oldest_index());

	sample last = buffer.get_oldest();
	printf("last: %ld\n", last.time_us);

	sample latest = buffer.get_newest();
	printf("latest: %ld\n", latest.time_us);

	sample mm;
	buffer.pop_first_older_than(2999, &mm);
	printf("mm: %ld\n", mm.time_us);


	printf("size: %ld\n", sizeof(buffer));
	printf("size: %d\n", buffer.get_total_size());
	
	Vector3f v1(1,0,0);

	return 1;
}

*/