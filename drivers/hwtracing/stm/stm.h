<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * System Trace Module (STM) infraकाष्ठाure
 * Copyright (c) 2014, Intel Corporation.
 *
 * STM class implements generic infraकाष्ठाure क्रम  System Trace Module devices
 * as defined in MIPI STPv2 specअगरication.
 */

#अगर_अघोषित _STM_STM_H_
#घोषणा _STM_STM_H_

#समावेश <linux/configfs.h>

काष्ठा stp_policy;
काष्ठा stp_policy_node;
काष्ठा sपंचांग_protocol_driver;

पूर्णांक stp_configfs_init(व्योम);
व्योम stp_configfs_निकास(व्योम);

व्योम *stp_policy_node_priv(काष्ठा stp_policy_node *pn);

काष्ठा stp_master अणु
	अचिन्हित पूर्णांक	nr_मुक्त;
	अचिन्हित दीर्घ	chan_map[];
पूर्ण;

काष्ठा sपंचांग_device अणु
	काष्ठा device		dev;
	काष्ठा module		*owner;
	काष्ठा stp_policy	*policy;
	काष्ठा mutex		policy_mutex;
	पूर्णांक			major;
	अचिन्हित पूर्णांक		sw_nmasters;
	काष्ठा sपंचांग_data		*data;
	काष्ठा mutex		link_mutex;
	spinlock_t		link_lock;
	काष्ठा list_head	link_list;
	/* framing protocol in use */
	स्थिर काष्ठा sपंचांग_protocol_driver	*pdrv;
	स्थिर काष्ठा config_item_type		*pdrv_node_type;
	/* master allocation */
	spinlock_t		mc_lock;
	काष्ठा stp_master	*masters[];
पूर्ण;

#घोषणा to_sपंचांग_device(_d)				\
	container_of((_d), काष्ठा sपंचांग_device, dev)

काष्ठा stp_policy_node *
stp_policy_node_lookup(काष्ठा sपंचांग_device *sपंचांग, अक्षर *s);
व्योम stp_policy_node_put(काष्ठा stp_policy_node *policy_node);
व्योम stp_policy_unbind(काष्ठा stp_policy *policy);

व्योम stp_policy_node_get_ranges(काष्ठा stp_policy_node *policy_node,
				अचिन्हित पूर्णांक *mstart, अचिन्हित पूर्णांक *mend,
				अचिन्हित पूर्णांक *cstart, अचिन्हित पूर्णांक *cend);

स्थिर काष्ठा config_item_type *
get_policy_node_type(काष्ठा configfs_attribute **attrs);

काष्ठा sपंचांग_output अणु
	spinlock_t		lock;
	अचिन्हित पूर्णांक		master;
	अचिन्हित पूर्णांक		channel;
	अचिन्हित पूर्णांक		nr_chans;
	व्योम			*pdrv_निजी;
पूर्ण;

काष्ठा sपंचांग_file अणु
	काष्ठा sपंचांग_device	*sपंचांग;
	काष्ठा sपंचांग_output	output;
पूर्ण;

काष्ठा sपंचांग_device *sपंचांग_find_device(स्थिर अक्षर *name);
व्योम sपंचांग_put_device(काष्ठा sपंचांग_device *sपंचांग);

काष्ठा sपंचांग_source_device अणु
	काष्ठा device		dev;
	काष्ठा sपंचांग_source_data	*data;
	spinlock_t		link_lock;
	काष्ठा sपंचांग_device __rcu	*link;
	काष्ठा list_head	link_entry;
	/* one output per sपंचांग_source device */
	काष्ठा sपंचांग_output	output;
पूर्ण;

#घोषणा to_sपंचांग_source_device(_d)				\
	container_of((_d), काष्ठा sपंचांग_source_device, dev)

व्योम *to_pdrv_policy_node(काष्ठा config_item *item);

काष्ठा sपंचांग_protocol_driver अणु
	काष्ठा module	*owner;
	स्थिर अक्षर	*name;
	sमाप_प्रकार		(*ग_लिखो)(काष्ठा sपंचांग_data *data,
				 काष्ठा sपंचांग_output *output, अचिन्हित पूर्णांक chan,
				 स्थिर अक्षर *buf, माप_प्रकार count);
	व्योम		(*policy_node_init)(व्योम *arg);
	पूर्णांक		(*output_खोलो)(व्योम *priv, काष्ठा sपंचांग_output *output);
	व्योम		(*output_बंद)(काष्ठा sपंचांग_output *output);
	sमाप_प्रकार		priv_sz;
	काष्ठा configfs_attribute	**policy_attr;
पूर्ण;

पूर्णांक sपंचांग_रेजिस्टर_protocol(स्थिर काष्ठा sपंचांग_protocol_driver *pdrv);
व्योम sपंचांग_unरेजिस्टर_protocol(स्थिर काष्ठा sपंचांग_protocol_driver *pdrv);
पूर्णांक sपंचांग_lookup_protocol(स्थिर अक्षर *name,
			स्थिर काष्ठा sपंचांग_protocol_driver **pdrv,
			स्थिर काष्ठा config_item_type **type);
व्योम sपंचांग_put_protocol(स्थिर काष्ठा sपंचांग_protocol_driver *pdrv);
sमाप_प्रकार sपंचांग_data_ग_लिखो(काष्ठा sपंचांग_data *data, अचिन्हित पूर्णांक m,
		       अचिन्हित पूर्णांक c, bool ts_first, स्थिर व्योम *buf,
		       माप_प्रकार count);

#पूर्ण_अगर /* _STM_STM_H_ */
