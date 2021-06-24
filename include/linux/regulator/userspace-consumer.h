<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __REGULATOR_PLATFORM_CONSUMER_H_
#घोषणा __REGULATOR_PLATFORM_CONSUMER_H_

काष्ठा regulator_consumer_supply;

/**
 * काष्ठा regulator_userspace_consumer_data - line consumer
 * initialisation data.
 *
 * @name: Name क्रम the consumer line
 * @num_supplies: Number of supplies feeding the line
 * @supplies: Supplies configuration.
 * @init_on: Set अगर the regulators supplying the line should be
 *           enabled during initialisation
 */
काष्ठा regulator_userspace_consumer_data अणु
	स्थिर अक्षर *name;

	पूर्णांक num_supplies;
	काष्ठा regulator_bulk_data *supplies;

	bool init_on;
पूर्ण;

#पूर्ण_अगर /* __REGULATOR_PLATFORM_CONSUMER_H_ */
