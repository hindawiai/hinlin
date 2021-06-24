<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bench.h"

/* COUNT-GLOBAL benchmark */

अटल काष्ठा count_global_ctx अणु
	काष्ठा counter hits;
पूर्ण count_global_ctx;

अटल व्योम *count_global_producer(व्योम *input)
अणु
	काष्ठा count_global_ctx *ctx = &count_global_ctx;

	जबतक (true) अणु
		atomic_inc(&ctx->hits.value);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *count_global_consumer(व्योम *input)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम count_global_measure(काष्ठा bench_res *res)
अणु
	काष्ठा count_global_ctx *ctx = &count_global_ctx;

	res->hits = atomic_swap(&ctx->hits.value, 0);
पूर्ण

/* COUNT-local benchmark */

अटल काष्ठा count_local_ctx अणु
	काष्ठा counter *hits;
पूर्ण count_local_ctx;

अटल व्योम count_local_setup()
अणु
	काष्ठा count_local_ctx *ctx = &count_local_ctx;

	ctx->hits = सुस्मृति(env.consumer_cnt, माप(*ctx->hits));
	अगर (!ctx->hits)
		निकास(1);
पूर्ण

अटल व्योम *count_local_producer(व्योम *input)
अणु
	काष्ठा count_local_ctx *ctx = &count_local_ctx;
	पूर्णांक idx = (दीर्घ)input;

	जबतक (true) अणु
		atomic_inc(&ctx->hits[idx].value);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *count_local_consumer(व्योम *input)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम count_local_measure(काष्ठा bench_res *res)
अणु
	काष्ठा count_local_ctx *ctx = &count_local_ctx;
	पूर्णांक i;

	क्रम (i = 0; i < env.producer_cnt; i++) अणु
		res->hits += atomic_swap(&ctx->hits[i].value, 0);
	पूर्ण
पूर्ण

स्थिर काष्ठा bench bench_count_global = अणु
	.name = "count-global",
	.producer_thपढ़ो = count_global_producer,
	.consumer_thपढ़ो = count_global_consumer,
	.measure = count_global_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;

स्थिर काष्ठा bench bench_count_local = अणु
	.name = "count-local",
	.setup = count_local_setup,
	.producer_thपढ़ो = count_local_producer,
	.consumer_thपढ़ो = count_local_consumer,
	.measure = count_local_measure,
	.report_progress = hits_drops_report_progress,
	.report_final = hits_drops_report_final,
पूर्ण;
