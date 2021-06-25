<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित COMPONENT_H
#घोषणा COMPONENT_H

#समावेश <linux/मानकघोष.स>


काष्ठा device;

/**
 * काष्ठा component_ops - callbacks क्रम component drivers
 *
 * Components are रेजिस्टरed with component_add() and unरेजिस्टरed with
 * component_del().
 */
काष्ठा component_ops अणु
	/**
	 * @bind:
	 *
	 * Called through component_bind_all() when the aggregate driver is
	 * पढ़ोy to bind the overall driver.
	 */
	पूर्णांक (*bind)(काष्ठा device *comp, काष्ठा device *master,
		    व्योम *master_data);
	/**
	 * @unbind:
	 *
	 * Called through component_unbind_all() when the aggregate driver is
	 * पढ़ोy to bind the overall driver, or when component_bind_all() fails
	 * part-ways through and needs to unbind some alपढ़ोy bound components.
	 */
	व्योम (*unbind)(काष्ठा device *comp, काष्ठा device *master,
		       व्योम *master_data);
पूर्ण;

पूर्णांक component_add(काष्ठा device *, स्थिर काष्ठा component_ops *);
पूर्णांक component_add_typed(काष्ठा device *dev, स्थिर काष्ठा component_ops *ops,
	पूर्णांक subcomponent);
व्योम component_del(काष्ठा device *, स्थिर काष्ठा component_ops *);

पूर्णांक component_bind_all(काष्ठा device *master, व्योम *master_data);
व्योम component_unbind_all(काष्ठा device *master, व्योम *master_data);

काष्ठा master;

/**
 * काष्ठा component_master_ops - callback क्रम the aggregate driver
 *
 * Aggregate drivers are रेजिस्टरed with component_master_add_with_match() and
 * unरेजिस्टरed with component_master_del().
 */
काष्ठा component_master_ops अणु
	/**
	 * @bind:
	 *
	 * Called when all components or the aggregate driver, as specअगरied in
	 * the match list passed to component_master_add_with_match(), are
	 * पढ़ोy. Usually there are 3 steps to bind an aggregate driver:
	 *
	 * 1. Allocate a काष्ठाure क्रम the aggregate driver.
	 *
	 * 2. Bind all components to the aggregate driver by calling
	 *    component_bind_all() with the aggregate driver काष्ठाure as opaque
	 *    poपूर्णांकer data.
	 *
	 * 3. Register the aggregate driver with the subप्रणाली to publish its
	 *    पूर्णांकerfaces.
	 *
	 * Note that the lअगरeसमय of the aggregate driver करोes not align with
	 * any of the underlying &काष्ठा device instances. Thereक्रमe devm cannot
	 * be used and all resources acquired or allocated in this callback must
	 * be explicitly released in the @unbind callback.
	 */
	पूर्णांक (*bind)(काष्ठा device *master);
	/**
	 * @unbind:
	 *
	 * Called when either the aggregate driver, using
	 * component_master_del(), or one of its components, using
	 * component_del(), is unरेजिस्टरed.
	 */
	व्योम (*unbind)(काष्ठा device *master);
पूर्ण;

व्योम component_master_del(काष्ठा device *,
	स्थिर काष्ठा component_master_ops *);

काष्ठा component_match;

पूर्णांक component_master_add_with_match(काष्ठा device *,
	स्थिर काष्ठा component_master_ops *, काष्ठा component_match *);
व्योम component_match_add_release(काष्ठा device *master,
	काष्ठा component_match **matchptr,
	व्योम (*release)(काष्ठा device *, व्योम *),
	पूर्णांक (*compare)(काष्ठा device *, व्योम *), व्योम *compare_data);
व्योम component_match_add_typed(काष्ठा device *master,
	काष्ठा component_match **matchptr,
	पूर्णांक (*compare_typed)(काष्ठा device *, पूर्णांक, व्योम *), व्योम *compare_data);

/**
 * component_match_add - add a component match entry
 * @master: device with the aggregate driver
 * @matchptr: poपूर्णांकer to the list of component matches
 * @compare: compare function to match against all components
 * @compare_data: opaque poपूर्णांकer passed to the @compare function
 *
 * Adds a new component match to the list stored in @matchptr, which the @master
 * aggregate driver needs to function. The list of component matches poपूर्णांकed to
 * by @matchptr must be initialized to शून्य beक्रमe adding the first match. This
 * only matches against components added with component_add().
 *
 * The allocated match list in @matchptr is स्वतःmatically released using devm
 * actions.
 *
 * See also component_match_add_release() and component_match_add_typed().
 */
अटल अंतरभूत व्योम component_match_add(काष्ठा device *master,
	काष्ठा component_match **matchptr,
	पूर्णांक (*compare)(काष्ठा device *, व्योम *), व्योम *compare_data)
अणु
	component_match_add_release(master, matchptr, शून्य, compare,
				    compare_data);
पूर्ण

#पूर्ण_अगर
