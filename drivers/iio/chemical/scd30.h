<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCD30_H
#घोषणा _SCD30_H

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/types.h>

काष्ठा scd30_state;

क्रमागत scd30_cmd अणु
	/* start continuous measurement with pressure compensation */
	CMD_START_MEAS,
	/* stop continuous measurement */
	CMD_STOP_MEAS,
	/* set/get measurement पूर्णांकerval */
	CMD_MEAS_INTERVAL,
	/* check whether new measurement is पढ़ोy */
	CMD_MEAS_READY,
	/* get measurement */
	CMD_READ_MEAS,
	/* turn on/off स्वतःmatic self calibration */
	CMD_ASC,
	/* set/get क्रमced recalibration value */
	CMD_FRC,
	/* set/get temperature offset */
	CMD_TEMP_OFFSET,
	/* get firmware version */
	CMD_FW_VERSION,
	/* reset sensor */
	CMD_RESET,
	/*
	 * Command क्रम altitude compensation was omitted पूर्णांकentionally because
	 * the same can be achieved by means of CMD_START_MEAS which takes
	 * pressure above the sea level as an argument.
	 */
पूर्ण;

#घोषणा SCD30_MEAS_COUNT 3

प्रकार पूर्णांक (*scd30_command_t)(काष्ठा scd30_state *state, क्रमागत scd30_cmd cmd, u16 arg,
			       व्योम *response, पूर्णांक size);

काष्ठा scd30_state अणु
	/* serialize access to the device */
	काष्ठा mutex lock;
	काष्ठा device *dev;
	काष्ठा regulator *vdd;
	काष्ठा completion meas_पढ़ोy;
	/*
	 * priv poपूर्णांकer is solely क्रम serdev driver निजी data. We keep it
	 * here because driver_data inside dev has been alपढ़ोy used क्रम iio and
	 * काष्ठा serdev_device करोesn't have one.
	 */
	व्योम *priv;
	पूर्णांक irq;
	/*
	 * no way to retrieve current ambient pressure compensation value from
	 * the sensor so keep one around
	 */
	u16 pressure_comp;
	u16 meas_पूर्णांकerval;
	पूर्णांक meas[SCD30_MEAS_COUNT];

	scd30_command_t command;
पूर्ण;

पूर्णांक scd30_suspend(काष्ठा device *dev);
पूर्णांक scd30_resume(काष्ठा device *dev);

अटल __maybe_unused SIMPLE_DEV_PM_OPS(scd30_pm_ops, scd30_suspend, scd30_resume);

पूर्णांक scd30_probe(काष्ठा device *dev, पूर्णांक irq, स्थिर अक्षर *name, व्योम *priv, scd30_command_t command);

#पूर्ण_अगर
