<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Loopback bridge driver क्रम the Greybus loopback module.
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sizes.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/atomic.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/greybus.h>
#समावेश <यंत्र/भाग64.h>

#घोषणा NSEC_PER_DAY 86400000000000ULL

काष्ठा gb_loopback_stats अणु
	u32 min;
	u32 max;
	u64 sum;
	u32 count;
पूर्ण;

काष्ठा gb_loopback_device अणु
	काष्ठा dentry *root;
	u32 count;
	माप_प्रकार size_max;

	/* We need to take a lock in atomic context */
	spinlock_t lock;
	रुको_queue_head_t wq;
पूर्ण;

अटल काष्ठा gb_loopback_device gb_dev;

काष्ठा gb_loopback_async_operation अणु
	काष्ठा gb_loopback *gb;
	काष्ठा gb_operation *operation;
	kसमय_प्रकार ts;
	पूर्णांक (*completion)(काष्ठा gb_loopback_async_operation *op_async);
पूर्ण;

काष्ठा gb_loopback अणु
	काष्ठा gb_connection *connection;

	काष्ठा dentry *file;
	काष्ठा kfअगरo kfअगरo_lat;
	काष्ठा mutex mutex;
	काष्ठा task_काष्ठा *task;
	काष्ठा device *dev;
	रुको_queue_head_t wq;
	रुको_queue_head_t wq_completion;
	atomic_t outstanding_operations;

	/* Per connection stats */
	kसमय_प्रकार ts;
	काष्ठा gb_loopback_stats latency;
	काष्ठा gb_loopback_stats throughput;
	काष्ठा gb_loopback_stats requests_per_second;
	काष्ठा gb_loopback_stats apbridge_unipro_latency;
	काष्ठा gb_loopback_stats gbphy_firmware_latency;

	पूर्णांक type;
	पूर्णांक async;
	पूर्णांक id;
	u32 size;
	u32 iteration_max;
	u32 iteration_count;
	पूर्णांक us_रुको;
	u32 error;
	u32 requests_completed;
	u32 requests_समयकरोut;
	u32 समयout;
	u32 jअगरfy_समयout;
	u32 समयout_min;
	u32 समयout_max;
	u32 outstanding_operations_max;
	u64 elapsed_nsecs;
	u32 apbridge_latency_ts;
	u32 gbphy_latency_ts;

	u32 send_count;
पूर्ण;

अटल काष्ठा class loopback_class = अणु
	.name		= "gb_loopback",
	.owner		= THIS_MODULE,
पूर्ण;
अटल DEFINE_IDA(loopback_ida);

/* Min/max values in jअगरfies */
#घोषणा GB_LOOPBACK_TIMEOUT_MIN				1
#घोषणा GB_LOOPBACK_TIMEOUT_MAX				10000

#घोषणा GB_LOOPBACK_FIFO_DEFAULT			8192

अटल अचिन्हित पूर्णांक kfअगरo_depth = GB_LOOPBACK_FIFO_DEFAULT;
module_param(kfअगरo_depth, uपूर्णांक, 0444);

/* Maximum size of any one send data buffer we support */
#घोषणा MAX_PACKET_SIZE (PAGE_SIZE * 2)

#घोषणा GB_LOOPBACK_US_WAIT_MAX				1000000

/* पूर्णांकerface sysfs attributes */
#घोषणा gb_loopback_ro_attr(field)				\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,			\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा gb_loopback *gb = dev_get_drvdata(dev);			\
	वापस प्र_लिखो(buf, "%u\n", gb->field);			\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

#घोषणा gb_loopback_ro_stats_attr(name, field, type)		\
अटल sमाप_प्रकार name##_##field##_show(काष्ठा device *dev,	\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा gb_loopback *gb = dev_get_drvdata(dev);			\
	/* Report 0 क्रम min and max अगर no transfer succeeded */		\
	अगर (!gb->requests_completed)					\
		वापस प्र_लिखो(buf, "0\n");				\
	वापस प्र_लिखो(buf, "%" #type "\n", gb->name.field);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(name##_##field)

#घोषणा gb_loopback_ro_avg_attr(name)			\
अटल sमाप_प्रकार name##_avg_show(काष्ठा device *dev,		\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा gb_loopback_stats *stats;				\
	काष्ठा gb_loopback *gb;						\
	u64 avg, rem;							\
	u32 count;							\
	gb = dev_get_drvdata(dev);			\
	stats = &gb->name;					\
	count = stats->count ? stats->count : 1;			\
	avg = stats->sum + count / 2000000; /* round बंदst */		\
	rem = करो_भाग(avg, count);					\
	rem *= 1000000;							\
	करो_भाग(rem, count);						\
	वापस प्र_लिखो(buf, "%llu.%06u\n", avg, (u32)rem);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(name##_avg)

#घोषणा gb_loopback_stats_attrs(field)				\
	gb_loopback_ro_stats_attr(field, min, u);		\
	gb_loopback_ro_stats_attr(field, max, u);		\
	gb_loopback_ro_avg_attr(field)

#घोषणा gb_loopback_attr(field, type)					\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा gb_loopback *gb = dev_get_drvdata(dev);			\
	वापस प्र_लिखो(buf, "%" #type "\n", gb->field);			\
पूर्ण									\
अटल sमाप_प्रकार field##_store(काष्ठा device *dev,			\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf,				\
			    माप_प्रकार len)					\
अणु									\
	पूर्णांक ret;							\
	काष्ठा gb_loopback *gb = dev_get_drvdata(dev);			\
	mutex_lock(&gb->mutex);						\
	ret = माला_पूछो(buf, "%"#type, &gb->field);			\
	अगर (ret != 1)							\
		len = -EINVAL;						\
	अन्यथा								\
		gb_loopback_check_attr(gb, bundle);			\
	mutex_unlock(&gb->mutex);					\
	वापस len;							\
पूर्ण									\
अटल DEVICE_ATTR_RW(field)

#घोषणा gb_dev_loopback_ro_attr(field, conn)				\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,		\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा gb_loopback *gb = dev_get_drvdata(dev);			\
	वापस प्र_लिखो(buf, "%u\n", gb->field);				\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

#घोषणा gb_dev_loopback_rw_attr(field, type)				\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा gb_loopback *gb = dev_get_drvdata(dev);			\
	वापस प्र_लिखो(buf, "%" #type "\n", gb->field);			\
पूर्ण									\
अटल sमाप_प्रकार field##_store(काष्ठा device *dev,			\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf,				\
			    माप_प्रकार len)					\
अणु									\
	पूर्णांक ret;							\
	काष्ठा gb_loopback *gb = dev_get_drvdata(dev);			\
	mutex_lock(&gb->mutex);						\
	ret = माला_पूछो(buf, "%"#type, &gb->field);			\
	अगर (ret != 1)							\
		len = -EINVAL;						\
	अन्यथा								\
		gb_loopback_check_attr(gb);		\
	mutex_unlock(&gb->mutex);					\
	वापस len;							\
पूर्ण									\
अटल DEVICE_ATTR_RW(field)

अटल व्योम gb_loopback_reset_stats(काष्ठा gb_loopback *gb);
अटल व्योम gb_loopback_check_attr(काष्ठा gb_loopback *gb)
अणु
	अगर (gb->us_रुको > GB_LOOPBACK_US_WAIT_MAX)
		gb->us_रुको = GB_LOOPBACK_US_WAIT_MAX;
	अगर (gb->size > gb_dev.size_max)
		gb->size = gb_dev.size_max;
	gb->requests_समयकरोut = 0;
	gb->requests_completed = 0;
	gb->iteration_count = 0;
	gb->send_count = 0;
	gb->error = 0;

	अगर (kfअगरo_depth < gb->iteration_max) अणु
		dev_warn(gb->dev,
			 "cannot log bytes %u kfifo_depth %u\n",
			 gb->iteration_max, kfअगरo_depth);
	पूर्ण
	kfअगरo_reset_out(&gb->kfअगरo_lat);

	चयन (gb->type) अणु
	हाल GB_LOOPBACK_TYPE_PING:
	हाल GB_LOOPBACK_TYPE_TRANSFER:
	हाल GB_LOOPBACK_TYPE_SINK:
		gb->jअगरfy_समयout = usecs_to_jअगरfies(gb->समयout);
		अगर (!gb->jअगरfy_समयout)
			gb->jअगरfy_समयout = GB_LOOPBACK_TIMEOUT_MIN;
		अन्यथा अगर (gb->jअगरfy_समयout > GB_LOOPBACK_TIMEOUT_MAX)
			gb->jअगरfy_समयout = GB_LOOPBACK_TIMEOUT_MAX;
		gb_loopback_reset_stats(gb);
		wake_up(&gb->wq);
		अवरोध;
	शेष:
		gb->type = 0;
		अवरोध;
	पूर्ण
पूर्ण

/* Time to send and receive one message */
gb_loopback_stats_attrs(latency);
/* Number of requests sent per second on this cport */
gb_loopback_stats_attrs(requests_per_second);
/* Quantity of data sent and received on this cport */
gb_loopback_stats_attrs(throughput);
/* Latency across the UniPro link from APBridge's perspective */
gb_loopback_stats_attrs(apbridge_unipro_latency);
/* Firmware induced overhead in the GPBridge */
gb_loopback_stats_attrs(gbphy_firmware_latency);

/* Number of errors encountered during loop */
gb_loopback_ro_attr(error);
/* Number of requests successfully completed async */
gb_loopback_ro_attr(requests_completed);
/* Number of requests समयd out async */
gb_loopback_ro_attr(requests_समयकरोut);
/* Timeout minimum in useconds */
gb_loopback_ro_attr(समयout_min);
/* Timeout minimum in useconds */
gb_loopback_ro_attr(समयout_max);

/*
 * Type of loopback message to send based on protocol type definitions
 * 0 => Don't send message
 * 2 => Send ping message continuously (message without payload)
 * 3 => Send transfer message continuously (message with payload,
 *					   payload वापसed in response)
 * 4 => Send a sink message (message with payload, no payload in response)
 */
gb_dev_loopback_rw_attr(type, d);
/* Size of transfer message payload: 0-4096 bytes */
gb_dev_loopback_rw_attr(size, u);
/* Time to रुको between two messages: 0-1000 ms */
gb_dev_loopback_rw_attr(us_रुको, d);
/* Maximum iterations क्रम a given operation: 1-(2^32-1), 0 implies infinite */
gb_dev_loopback_rw_attr(iteration_max, u);
/* The current index of the क्रम (i = 0; i < iteration_max; i++) loop */
gb_dev_loopback_ro_attr(iteration_count, false);
/* A flag to indicate synchronous or asynchronous operations */
gb_dev_loopback_rw_attr(async, u);
/* Timeout of an inभागidual asynchronous request */
gb_dev_loopback_rw_attr(समयout, u);
/* Maximum number of in-flight operations beक्रमe back-off */
gb_dev_loopback_rw_attr(outstanding_operations_max, u);

अटल काष्ठा attribute *loopback_attrs[] = अणु
	&dev_attr_latency_min.attr,
	&dev_attr_latency_max.attr,
	&dev_attr_latency_avg.attr,
	&dev_attr_requests_per_second_min.attr,
	&dev_attr_requests_per_second_max.attr,
	&dev_attr_requests_per_second_avg.attr,
	&dev_attr_throughput_min.attr,
	&dev_attr_throughput_max.attr,
	&dev_attr_throughput_avg.attr,
	&dev_attr_apbridge_unipro_latency_min.attr,
	&dev_attr_apbridge_unipro_latency_max.attr,
	&dev_attr_apbridge_unipro_latency_avg.attr,
	&dev_attr_gbphy_firmware_latency_min.attr,
	&dev_attr_gbphy_firmware_latency_max.attr,
	&dev_attr_gbphy_firmware_latency_avg.attr,
	&dev_attr_type.attr,
	&dev_attr_size.attr,
	&dev_attr_us_रुको.attr,
	&dev_attr_iteration_count.attr,
	&dev_attr_iteration_max.attr,
	&dev_attr_async.attr,
	&dev_attr_error.attr,
	&dev_attr_requests_completed.attr,
	&dev_attr_requests_समयकरोut.attr,
	&dev_attr_समयout.attr,
	&dev_attr_outstanding_operations_max.attr,
	&dev_attr_समयout_min.attr,
	&dev_attr_समयout_max.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(loopback);

अटल व्योम gb_loopback_calculate_stats(काष्ठा gb_loopback *gb, bool error);

अटल u32 gb_loopback_nsec_to_usec_latency(u64 elapsed_nsecs)
अणु
	करो_भाग(elapsed_nsecs, NSEC_PER_USEC);
	वापस elapsed_nsecs;
पूर्ण

अटल u64 __gb_loopback_calc_latency(u64 t1, u64 t2)
अणु
	अगर (t2 > t1)
		वापस t2 - t1;
	अन्यथा
		वापस NSEC_PER_DAY - t2 + t1;
पूर्ण

अटल u64 gb_loopback_calc_latency(kसमय_प्रकार ts, kसमय_प्रकार te)
अणु
	वापस __gb_loopback_calc_latency(kसमय_प्रकारo_ns(ts), kसमय_प्रकारo_ns(te));
पूर्ण

अटल पूर्णांक gb_loopback_operation_sync(काष्ठा gb_loopback *gb, पूर्णांक type,
				      व्योम *request, पूर्णांक request_size,
				      व्योम *response, पूर्णांक response_size)
अणु
	काष्ठा gb_operation *operation;
	kसमय_प्रकार ts, te;
	पूर्णांक ret;

	ts = kसमय_get();
	operation = gb_operation_create(gb->connection, type, request_size,
					response_size, GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	अगर (request_size)
		स_नकल(operation->request->payload, request, request_size);

	ret = gb_operation_request_send_sync(operation);
	अगर (ret) अणु
		dev_err(&gb->connection->bundle->dev,
			"synchronous operation failed: %d\n", ret);
		जाओ out_put_operation;
	पूर्ण अन्यथा अणु
		अगर (response_size == operation->response->payload_size) अणु
			स_नकल(response, operation->response->payload,
			       response_size);
		पूर्ण अन्यथा अणु
			dev_err(&gb->connection->bundle->dev,
				"response size %zu expected %d\n",
				operation->response->payload_size,
				response_size);
			ret = -EINVAL;
			जाओ out_put_operation;
		पूर्ण
	पूर्ण

	te = kसमय_get();

	/* Calculate the total समय the message took */
	gb->elapsed_nsecs = gb_loopback_calc_latency(ts, te);

out_put_operation:
	gb_operation_put(operation);

	वापस ret;
पूर्ण

अटल व्योम gb_loopback_async_रुको_all(काष्ठा gb_loopback *gb)
अणु
	रुको_event(gb->wq_completion,
		   !atomic_पढ़ो(&gb->outstanding_operations));
पूर्ण

अटल व्योम gb_loopback_async_operation_callback(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_loopback_async_operation *op_async;
	काष्ठा gb_loopback *gb;
	kसमय_प्रकार te;
	पूर्णांक result;

	te = kसमय_get();
	result = gb_operation_result(operation);
	op_async = gb_operation_get_data(operation);
	gb = op_async->gb;

	mutex_lock(&gb->mutex);

	अगर (!result && op_async->completion)
		result = op_async->completion(op_async);

	अगर (!result) अणु
		gb->elapsed_nsecs = gb_loopback_calc_latency(op_async->ts, te);
	पूर्ण अन्यथा अणु
		gb->error++;
		अगर (result == -ETIMEDOUT)
			gb->requests_समयकरोut++;
	पूर्ण

	gb->iteration_count++;
	gb_loopback_calculate_stats(gb, result);

	mutex_unlock(&gb->mutex);

	dev_dbg(&gb->connection->bundle->dev, "complete operation %d\n",
		operation->id);

	/* Wake up रुकोers */
	atomic_dec(&op_async->gb->outstanding_operations);
	wake_up(&gb->wq_completion);

	/* Release resources */
	gb_operation_put(operation);
	kमुक्त(op_async);
पूर्ण

अटल पूर्णांक gb_loopback_async_operation(काष्ठा gb_loopback *gb, पूर्णांक type,
				       व्योम *request, पूर्णांक request_size,
				       पूर्णांक response_size,
				       व्योम *completion)
अणु
	काष्ठा gb_loopback_async_operation *op_async;
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	op_async = kzalloc(माप(*op_async), GFP_KERNEL);
	अगर (!op_async)
		वापस -ENOMEM;

	operation = gb_operation_create(gb->connection, type, request_size,
					response_size, GFP_KERNEL);
	अगर (!operation) अणु
		kमुक्त(op_async);
		वापस -ENOMEM;
	पूर्ण

	अगर (request_size)
		स_नकल(operation->request->payload, request, request_size);

	gb_operation_set_data(operation, op_async);

	op_async->gb = gb;
	op_async->operation = operation;
	op_async->completion = completion;

	op_async->ts = kसमय_get();

	atomic_inc(&gb->outstanding_operations);
	ret = gb_operation_request_send(operation,
					gb_loopback_async_operation_callback,
					jअगरfies_to_msecs(gb->jअगरfy_समयout),
					GFP_KERNEL);
	अगर (ret) अणु
		atomic_dec(&gb->outstanding_operations);
		gb_operation_put(operation);
		kमुक्त(op_async);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gb_loopback_sync_sink(काष्ठा gb_loopback *gb, u32 len)
अणु
	काष्ठा gb_loopback_transfer_request *request;
	पूर्णांक retval;

	request = kदो_स्मृति(len + माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	request->len = cpu_to_le32(len);
	retval = gb_loopback_operation_sync(gb, GB_LOOPBACK_TYPE_SINK,
					    request, len + माप(*request),
					    शून्य, 0);
	kमुक्त(request);
	वापस retval;
पूर्ण

अटल पूर्णांक gb_loopback_sync_transfer(काष्ठा gb_loopback *gb, u32 len)
अणु
	काष्ठा gb_loopback_transfer_request *request;
	काष्ठा gb_loopback_transfer_response *response;
	पूर्णांक retval;

	gb->apbridge_latency_ts = 0;
	gb->gbphy_latency_ts = 0;

	request = kदो_स्मृति(len + माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;
	response = kदो_स्मृति(len + माप(*response), GFP_KERNEL);
	अगर (!response) अणु
		kमुक्त(request);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(request->data, 0x5A, len);

	request->len = cpu_to_le32(len);
	retval = gb_loopback_operation_sync(gb, GB_LOOPBACK_TYPE_TRANSFER,
					    request, len + माप(*request),
					    response, len + माप(*response));
	अगर (retval)
		जाओ gb_error;

	अगर (स_भेद(request->data, response->data, len)) अणु
		dev_err(&gb->connection->bundle->dev,
			"Loopback Data doesn't match\n");
		retval = -EREMOTEIO;
	पूर्ण
	gb->apbridge_latency_ts = (u32)__le32_to_cpu(response->reserved0);
	gb->gbphy_latency_ts = (u32)__le32_to_cpu(response->reserved1);

gb_error:
	kमुक्त(request);
	kमुक्त(response);

	वापस retval;
पूर्ण

अटल पूर्णांक gb_loopback_sync_ping(काष्ठा gb_loopback *gb)
अणु
	वापस gb_loopback_operation_sync(gb, GB_LOOPBACK_TYPE_PING,
					  शून्य, 0, शून्य, 0);
पूर्ण

अटल पूर्णांक gb_loopback_async_sink(काष्ठा gb_loopback *gb, u32 len)
अणु
	काष्ठा gb_loopback_transfer_request *request;
	पूर्णांक retval;

	request = kदो_स्मृति(len + माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	request->len = cpu_to_le32(len);
	retval = gb_loopback_async_operation(gb, GB_LOOPBACK_TYPE_SINK,
					     request, len + माप(*request),
					     0, शून्य);
	kमुक्त(request);
	वापस retval;
पूर्ण

अटल पूर्णांक gb_loopback_async_transfer_complete(
				काष्ठा gb_loopback_async_operation *op_async)
अणु
	काष्ठा gb_loopback *gb;
	काष्ठा gb_operation *operation;
	काष्ठा gb_loopback_transfer_request *request;
	काष्ठा gb_loopback_transfer_response *response;
	माप_प्रकार len;
	पूर्णांक retval = 0;

	gb = op_async->gb;
	operation = op_async->operation;
	request = operation->request->payload;
	response = operation->response->payload;
	len = le32_to_cpu(request->len);

	अगर (स_भेद(request->data, response->data, len)) अणु
		dev_err(&gb->connection->bundle->dev,
			"Loopback Data doesn't match operation id %d\n",
			operation->id);
		retval = -EREMOTEIO;
	पूर्ण अन्यथा अणु
		gb->apbridge_latency_ts =
			(u32)__le32_to_cpu(response->reserved0);
		gb->gbphy_latency_ts =
			(u32)__le32_to_cpu(response->reserved1);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक gb_loopback_async_transfer(काष्ठा gb_loopback *gb, u32 len)
अणु
	काष्ठा gb_loopback_transfer_request *request;
	पूर्णांक retval, response_len;

	request = kदो_स्मृति(len + माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	स_रखो(request->data, 0x5A, len);

	request->len = cpu_to_le32(len);
	response_len = माप(काष्ठा gb_loopback_transfer_response);
	retval = gb_loopback_async_operation(gb, GB_LOOPBACK_TYPE_TRANSFER,
					     request, len + माप(*request),
					     len + response_len,
					     gb_loopback_async_transfer_complete);
	अगर (retval)
		जाओ gb_error;

gb_error:
	kमुक्त(request);
	वापस retval;
पूर्ण

अटल पूर्णांक gb_loopback_async_ping(काष्ठा gb_loopback *gb)
अणु
	वापस gb_loopback_async_operation(gb, GB_LOOPBACK_TYPE_PING,
					   शून्य, 0, 0, शून्य);
पूर्ण

अटल पूर्णांक gb_loopback_request_handler(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_connection *connection = operation->connection;
	काष्ठा gb_loopback_transfer_request *request;
	काष्ठा gb_loopback_transfer_response *response;
	काष्ठा device *dev = &connection->bundle->dev;
	माप_प्रकार len;

	/* By convention, the AP initiates the version operation */
	चयन (operation->type) अणु
	हाल GB_LOOPBACK_TYPE_PING:
	हाल GB_LOOPBACK_TYPE_SINK:
		वापस 0;
	हाल GB_LOOPBACK_TYPE_TRANSFER:
		अगर (operation->request->payload_size < माप(*request)) अणु
			dev_err(dev, "transfer request too small (%zu < %zu)\n",
				operation->request->payload_size,
				माप(*request));
			वापस -EINVAL;	/* -EMSGSIZE */
		पूर्ण
		request = operation->request->payload;
		len = le32_to_cpu(request->len);
		अगर (len > gb_dev.size_max) अणु
			dev_err(dev, "transfer request too large (%zu > %zu)\n",
				len, gb_dev.size_max);
			वापस -EINVAL;
		पूर्ण

		अगर (!gb_operation_response_alloc(operation,
				len + माप(*response), GFP_KERNEL)) अणु
			dev_err(dev, "error allocating response\n");
			वापस -ENOMEM;
		पूर्ण
		response = operation->response->payload;
		response->len = cpu_to_le32(len);
		अगर (len)
			स_नकल(response->data, request->data, len);

		वापस 0;
	शेष:
		dev_err(dev, "unsupported request: %u\n", operation->type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम gb_loopback_reset_stats(काष्ठा gb_loopback *gb)
अणु
	काष्ठा gb_loopback_stats reset = अणु
		.min = U32_MAX,
	पूर्ण;

	/* Reset per-connection stats */
	स_नकल(&gb->latency, &reset,
	       माप(काष्ठा gb_loopback_stats));
	स_नकल(&gb->throughput, &reset,
	       माप(काष्ठा gb_loopback_stats));
	स_नकल(&gb->requests_per_second, &reset,
	       माप(काष्ठा gb_loopback_stats));
	स_नकल(&gb->apbridge_unipro_latency, &reset,
	       माप(काष्ठा gb_loopback_stats));
	स_नकल(&gb->gbphy_firmware_latency, &reset,
	       माप(काष्ठा gb_loopback_stats));

	/* Should be initialized at least once per transaction set */
	gb->apbridge_latency_ts = 0;
	gb->gbphy_latency_ts = 0;
	gb->ts = kसमय_set(0, 0);
पूर्ण

अटल व्योम gb_loopback_update_stats(काष्ठा gb_loopback_stats *stats, u32 val)
अणु
	अगर (stats->min > val)
		stats->min = val;
	अगर (stats->max < val)
		stats->max = val;
	stats->sum += val;
	stats->count++;
पूर्ण

अटल व्योम gb_loopback_update_stats_winकरोw(काष्ठा gb_loopback_stats *stats,
					    u64 val, u32 count)
अणु
	stats->sum += val;
	stats->count += count;

	करो_भाग(val, count);
	अगर (stats->min > val)
		stats->min = val;
	अगर (stats->max < val)
		stats->max = val;
पूर्ण

अटल व्योम gb_loopback_requests_update(काष्ठा gb_loopback *gb, u32 latency)
अणु
	u64 req = gb->requests_completed * USEC_PER_SEC;

	gb_loopback_update_stats_winकरोw(&gb->requests_per_second, req, latency);
पूर्ण

अटल व्योम gb_loopback_throughput_update(काष्ठा gb_loopback *gb, u32 latency)
अणु
	u64 aggregate_size = माप(काष्ठा gb_operation_msg_hdr) * 2;

	चयन (gb->type) अणु
	हाल GB_LOOPBACK_TYPE_PING:
		अवरोध;
	हाल GB_LOOPBACK_TYPE_SINK:
		aggregate_size += माप(काष्ठा gb_loopback_transfer_request) +
				  gb->size;
		अवरोध;
	हाल GB_LOOPBACK_TYPE_TRANSFER:
		aggregate_size += माप(काष्ठा gb_loopback_transfer_request) +
				  माप(काष्ठा gb_loopback_transfer_response) +
				  gb->size * 2;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	aggregate_size *= gb->requests_completed;
	aggregate_size *= USEC_PER_SEC;
	gb_loopback_update_stats_winकरोw(&gb->throughput, aggregate_size,
					latency);
पूर्ण

अटल व्योम gb_loopback_calculate_latency_stats(काष्ठा gb_loopback *gb)
अणु
	u32 lat;

	/* Express latency in terms of microseconds */
	lat = gb_loopback_nsec_to_usec_latency(gb->elapsed_nsecs);

	/* Log latency stastic */
	gb_loopback_update_stats(&gb->latency, lat);

	/* Raw latency log on a per thपढ़ो basis */
	kfअगरo_in(&gb->kfअगरo_lat, (अचिन्हित अक्षर *)&lat, माप(lat));

	/* Log the firmware supplied latency values */
	gb_loopback_update_stats(&gb->apbridge_unipro_latency,
				 gb->apbridge_latency_ts);
	gb_loopback_update_stats(&gb->gbphy_firmware_latency,
				 gb->gbphy_latency_ts);
पूर्ण

अटल व्योम gb_loopback_calculate_stats(काष्ठा gb_loopback *gb, bool error)
अणु
	u64 nlat;
	u32 lat;
	kसमय_प्रकार te;

	अगर (!error) अणु
		gb->requests_completed++;
		gb_loopback_calculate_latency_stats(gb);
	पूर्ण

	te = kसमय_get();
	nlat = gb_loopback_calc_latency(gb->ts, te);
	अगर (nlat >= NSEC_PER_SEC || gb->iteration_count == gb->iteration_max) अणु
		lat = gb_loopback_nsec_to_usec_latency(nlat);

		gb_loopback_throughput_update(gb, lat);
		gb_loopback_requests_update(gb, lat);

		अगर (gb->iteration_count != gb->iteration_max) अणु
			gb->ts = te;
			gb->requests_completed = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gb_loopback_async_रुको_to_send(काष्ठा gb_loopback *gb)
अणु
	अगर (!(gb->async && gb->outstanding_operations_max))
		वापस;
	रुको_event_पूर्णांकerruptible(gb->wq_completion,
				 (atomic_पढ़ो(&gb->outstanding_operations) <
				  gb->outstanding_operations_max) ||
				  kthपढ़ो_should_stop());
पूर्ण

अटल पूर्णांक gb_loopback_fn(व्योम *data)
अणु
	पूर्णांक error = 0;
	पूर्णांक us_रुको = 0;
	पूर्णांक type;
	पूर्णांक ret;
	u32 size;

	काष्ठा gb_loopback *gb = data;
	काष्ठा gb_bundle *bundle = gb->connection->bundle;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	जबतक (1) अणु
		अगर (!gb->type) अणु
			gb_pm_runसमय_put_स्वतःsuspend(bundle);
			रुको_event_पूर्णांकerruptible(gb->wq, gb->type ||
						 kthपढ़ो_should_stop());
			ret = gb_pm_runसमय_get_sync(bundle);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* Limit the maximum number of in-flight async operations */
		gb_loopback_async_रुको_to_send(gb);
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		mutex_lock(&gb->mutex);

		/* Optionally terminate */
		अगर (gb->send_count == gb->iteration_max) अणु
			mutex_unlock(&gb->mutex);

			/* Wait क्रम synchronous and asynchronus completion */
			gb_loopback_async_रुको_all(gb);

			/* Mark complete unless user-space has poked us */
			mutex_lock(&gb->mutex);
			अगर (gb->iteration_count == gb->iteration_max) अणु
				gb->type = 0;
				gb->send_count = 0;
				sysfs_notअगरy(&gb->dev->kobj,  शून्य,
					     "iteration_count");
				dev_dbg(&bundle->dev, "load test complete\n");
			पूर्ण अन्यथा अणु
				dev_dbg(&bundle->dev,
					"continuing on with new test set\n");
			पूर्ण
			mutex_unlock(&gb->mutex);
			जारी;
		पूर्ण
		size = gb->size;
		us_रुको = gb->us_रुको;
		type = gb->type;
		अगर (kसमय_प्रकारo_ns(gb->ts) == 0)
			gb->ts = kसमय_get();

		/* Else operations to perक्रमm */
		अगर (gb->async) अणु
			अगर (type == GB_LOOPBACK_TYPE_PING)
				error = gb_loopback_async_ping(gb);
			अन्यथा अगर (type == GB_LOOPBACK_TYPE_TRANSFER)
				error = gb_loopback_async_transfer(gb, size);
			अन्यथा अगर (type == GB_LOOPBACK_TYPE_SINK)
				error = gb_loopback_async_sink(gb, size);

			अगर (error) अणु
				gb->error++;
				gb->iteration_count++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* We are effectively single thपढ़ोed here */
			अगर (type == GB_LOOPBACK_TYPE_PING)
				error = gb_loopback_sync_ping(gb);
			अन्यथा अगर (type == GB_LOOPBACK_TYPE_TRANSFER)
				error = gb_loopback_sync_transfer(gb, size);
			अन्यथा अगर (type == GB_LOOPBACK_TYPE_SINK)
				error = gb_loopback_sync_sink(gb, size);

			अगर (error)
				gb->error++;
			gb->iteration_count++;
			gb_loopback_calculate_stats(gb, !!error);
		पूर्ण
		gb->send_count++;
		mutex_unlock(&gb->mutex);

		अगर (us_रुको) अणु
			अगर (us_रुको < 20000)
				usleep_range(us_रुको, us_रुको + 100);
			अन्यथा
				msleep(us_रुको / 1000);
		पूर्ण
	पूर्ण

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_loopback_dbgfs_latency_show_common(काष्ठा seq_file *s,
						 काष्ठा kfअगरo *kfअगरo,
						 काष्ठा mutex *mutex)
अणु
	u32 latency;
	पूर्णांक retval;

	अगर (kfअगरo_len(kfअगरo) == 0) अणु
		retval = -EAGAIN;
		जाओ करोne;
	पूर्ण

	mutex_lock(mutex);
	retval = kfअगरo_out(kfअगरo, &latency, माप(latency));
	अगर (retval > 0) अणु
		seq_म_लिखो(s, "%u", latency);
		retval = 0;
	पूर्ण
	mutex_unlock(mutex);
करोne:
	वापस retval;
पूर्ण

अटल पूर्णांक gb_loopback_dbgfs_latency_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा gb_loopback *gb = s->निजी;

	वापस gb_loopback_dbgfs_latency_show_common(s, &gb->kfअगरo_lat,
						     &gb->mutex);
पूर्ण
DEFINE_SHOW_ATTRIBUTE(gb_loopback_dbgfs_latency);

#घोषणा DEBUGFS_NAMELEN 32

अटल पूर्णांक gb_loopback_probe(काष्ठा gb_bundle *bundle,
			     स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा gb_loopback *gb;
	काष्ठा device *dev;
	पूर्णांक retval;
	अक्षर name[DEBUGFS_NAMELEN];
	अचिन्हित दीर्घ flags;

	अगर (bundle->num_cports != 1)
		वापस -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	अगर (cport_desc->protocol_id != GREYBUS_PROTOCOL_LOOPBACK)
		वापस -ENODEV;

	gb = kzalloc(माप(*gb), GFP_KERNEL);
	अगर (!gb)
		वापस -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_loopback_request_handler);
	अगर (IS_ERR(connection)) अणु
		retval = PTR_ERR(connection);
		जाओ out_kzalloc;
	पूर्ण

	gb->connection = connection;
	greybus_set_drvdata(bundle, gb);

	init_रुकोqueue_head(&gb->wq);
	init_रुकोqueue_head(&gb->wq_completion);
	atomic_set(&gb->outstanding_operations, 0);
	gb_loopback_reset_stats(gb);

	/* Reported values to user-space क्रम min/max समयouts */
	gb->समयout_min = jअगरfies_to_usecs(GB_LOOPBACK_TIMEOUT_MIN);
	gb->समयout_max = jअगरfies_to_usecs(GB_LOOPBACK_TIMEOUT_MAX);

	अगर (!gb_dev.count) अणु
		/* Calculate maximum payload */
		gb_dev.size_max = gb_operation_get_payload_size_max(connection);
		अगर (gb_dev.size_max <=
			माप(काष्ठा gb_loopback_transfer_request)) अणु
			retval = -EINVAL;
			जाओ out_connection_destroy;
		पूर्ण
		gb_dev.size_max -= माप(काष्ठा gb_loopback_transfer_request);
	पूर्ण

	/* Create per-connection sysfs and debugfs data-poपूर्णांकs */
	snम_लिखो(name, माप(name), "raw_latency_%s",
		 dev_name(&connection->bundle->dev));
	gb->file = debugfs_create_file(name, S_IFREG | 0444, gb_dev.root, gb,
				       &gb_loopback_dbgfs_latency_fops);

	gb->id = ida_simple_get(&loopback_ida, 0, 0, GFP_KERNEL);
	अगर (gb->id < 0) अणु
		retval = gb->id;
		जाओ out_debugfs_हटाओ;
	पूर्ण

	retval = gb_connection_enable(connection);
	अगर (retval)
		जाओ out_ida_हटाओ;

	dev = device_create_with_groups(&loopback_class,
					&connection->bundle->dev,
					MKDEV(0, 0), gb, loopback_groups,
					"gb_loopback%d", gb->id);
	अगर (IS_ERR(dev)) अणु
		retval = PTR_ERR(dev);
		जाओ out_connection_disable;
	पूर्ण
	gb->dev = dev;

	/* Allocate kfअगरo */
	अगर (kfअगरo_alloc(&gb->kfअगरo_lat, kfअगरo_depth * माप(u32),
			GFP_KERNEL)) अणु
		retval = -ENOMEM;
		जाओ out_conn;
	पूर्ण
	/* Fork worker thपढ़ो */
	mutex_init(&gb->mutex);
	gb->task = kthपढ़ो_run(gb_loopback_fn, gb, "gb_loopback");
	अगर (IS_ERR(gb->task)) अणु
		retval = PTR_ERR(gb->task);
		जाओ out_kfअगरo;
	पूर्ण

	spin_lock_irqsave(&gb_dev.lock, flags);
	gb_dev.count++;
	spin_unlock_irqrestore(&gb_dev.lock, flags);

	gb_connection_latency_tag_enable(connection);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस 0;

out_kfअगरo:
	kfअगरo_मुक्त(&gb->kfअगरo_lat);
out_conn:
	device_unरेजिस्टर(dev);
out_connection_disable:
	gb_connection_disable(connection);
out_ida_हटाओ:
	ida_simple_हटाओ(&loopback_ida, gb->id);
out_debugfs_हटाओ:
	debugfs_हटाओ(gb->file);
out_connection_destroy:
	gb_connection_destroy(connection);
out_kzalloc:
	kमुक्त(gb);

	वापस retval;
पूर्ण

अटल व्योम gb_loopback_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_loopback *gb = greybus_get_drvdata(bundle);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		gb_pm_runसमय_get_noresume(bundle);

	gb_connection_disable(gb->connection);

	अगर (!IS_ERR_OR_शून्य(gb->task))
		kthपढ़ो_stop(gb->task);

	kfअगरo_मुक्त(&gb->kfअगरo_lat);
	gb_connection_latency_tag_disable(gb->connection);
	debugfs_हटाओ(gb->file);

	/*
	 * FIXME: gb_loopback_async_रुको_all() is redundant now, as connection
	 * is disabled at the beginning and so we can't have any more
	 * incoming/outgoing requests.
	 */
	gb_loopback_async_रुको_all(gb);

	spin_lock_irqsave(&gb_dev.lock, flags);
	gb_dev.count--;
	spin_unlock_irqrestore(&gb_dev.lock, flags);

	device_unरेजिस्टर(gb->dev);
	ida_simple_हटाओ(&loopback_ida, gb->id);

	gb_connection_destroy(gb->connection);
	kमुक्त(gb);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_loopback_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_LOOPBACK) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_loopback_id_table);

अटल काष्ठा greybus_driver gb_loopback_driver = अणु
	.name		= "loopback",
	.probe		= gb_loopback_probe,
	.disconnect	= gb_loopback_disconnect,
	.id_table	= gb_loopback_id_table,
पूर्ण;

अटल पूर्णांक loopback_init(व्योम)
अणु
	पूर्णांक retval;

	spin_lock_init(&gb_dev.lock);
	gb_dev.root = debugfs_create_dir("gb_loopback", शून्य);

	retval = class_रेजिस्टर(&loopback_class);
	अगर (retval)
		जाओ err;

	retval = greybus_रेजिस्टर(&gb_loopback_driver);
	अगर (retval)
		जाओ err_unरेजिस्टर;

	वापस 0;

err_unरेजिस्टर:
	class_unरेजिस्टर(&loopback_class);
err:
	debugfs_हटाओ_recursive(gb_dev.root);
	वापस retval;
पूर्ण
module_init(loopback_init);

अटल व्योम __निकास loopback_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(gb_dev.root);
	greybus_deरेजिस्टर(&gb_loopback_driver);
	class_unरेजिस्टर(&loopback_class);
	ida_destroy(&loopback_ida);
पूर्ण
module_निकास(loopback_निकास);

MODULE_LICENSE("GPL v2");
