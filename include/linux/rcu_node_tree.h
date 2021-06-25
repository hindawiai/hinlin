<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * RCU node combining tree definitions.  These are used to compute
 * global attributes जबतक aव्योमing common-हाल global contention.  A key
 * property that these computations rely on is a tournament-style approach
 * where only one of the tasks contending a lower level in the tree need
 * advance to the next higher level.  If properly configured, this allows
 * unlimited scalability जबतक मुख्यtaining a स्थिरant level of contention
 * on the root node.
 *
 * This seemingly RCU-निजी file must be available to SRCU users
 * because the size of the TREE SRCU srcu_काष्ठा काष्ठाure depends
 * on these definitions.
 *
 * Copyright IBM Corporation, 2017
 *
 * Author: Paul E. McKenney <paulmck@linux.ibm.com>
 */

#अगर_अघोषित __LINUX_RCU_NODE_TREE_H
#घोषणा __LINUX_RCU_NODE_TREE_H

#समावेश <linux/गणित.स>

/*
 * Define shape of hierarchy based on NR_CPUS, CONFIG_RCU_FANOUT, and
 * CONFIG_RCU_FANOUT_LEAF.
 * In theory, it should be possible to add more levels straightक्रमwardly.
 * In practice, this did work well going from three levels to four.
 * Of course, your mileage may vary.
 */

#अगर_घोषित CONFIG_RCU_FANOUT
#घोषणा RCU_FANOUT CONFIG_RCU_FANOUT
#अन्यथा /* #अगर_घोषित CONFIG_RCU_FANOUT */
# अगरdef CONFIG_64BIT
# define RCU_FANOUT 64
# अन्यथा
# define RCU_FANOUT 32
# endअगर
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_FANOUT */

#अगर_घोषित CONFIG_RCU_FANOUT_LEAF
#घोषणा RCU_FANOUT_LEAF CONFIG_RCU_FANOUT_LEAF
#अन्यथा /* #अगर_घोषित CONFIG_RCU_FANOUT_LEAF */
#घोषणा RCU_FANOUT_LEAF 16
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_FANOUT_LEAF */

#घोषणा RCU_FANOUT_1	      (RCU_FANOUT_LEAF)
#घोषणा RCU_FANOUT_2	      (RCU_FANOUT_1 * RCU_FANOUT)
#घोषणा RCU_FANOUT_3	      (RCU_FANOUT_2 * RCU_FANOUT)
#घोषणा RCU_FANOUT_4	      (RCU_FANOUT_3 * RCU_FANOUT)

#अगर NR_CPUS <= RCU_FANOUT_1
#  define RCU_NUM_LVLS	      1
#  define NUM_RCU_LVL_0	      1
#  define NUM_RCU_NODES	      NUM_RCU_LVL_0
#  define NUM_RCU_LVL_INIT    अणु NUM_RCU_LVL_0 पूर्ण
#  define RCU_NODE_NAME_INIT  अणु "rcu_node_0" पूर्ण
#  define RCU_FQS_NAME_INIT   अणु "rcu_node_fqs_0" पूर्ण
#या_अगर NR_CPUS <= RCU_FANOUT_2
#  define RCU_NUM_LVLS	      2
#  define NUM_RCU_LVL_0	      1
#  define NUM_RCU_LVL_1	      DIV_ROUND_UP(NR_CPUS, RCU_FANOUT_1)
#  define NUM_RCU_NODES	      (NUM_RCU_LVL_0 + NUM_RCU_LVL_1)
#  define NUM_RCU_LVL_INIT    अणु NUM_RCU_LVL_0, NUM_RCU_LVL_1 पूर्ण
#  define RCU_NODE_NAME_INIT  अणु "rcu_node_0", "rcu_node_1" पूर्ण
#  define RCU_FQS_NAME_INIT   अणु "rcu_node_fqs_0", "rcu_node_fqs_1" पूर्ण
#या_अगर NR_CPUS <= RCU_FANOUT_3
#  define RCU_NUM_LVLS	      3
#  define NUM_RCU_LVL_0	      1
#  define NUM_RCU_LVL_1	      DIV_ROUND_UP(NR_CPUS, RCU_FANOUT_2)
#  define NUM_RCU_LVL_2	      DIV_ROUND_UP(NR_CPUS, RCU_FANOUT_1)
#  define NUM_RCU_NODES	      (NUM_RCU_LVL_0 + NUM_RCU_LVL_1 + NUM_RCU_LVL_2)
#  define NUM_RCU_LVL_INIT    अणु NUM_RCU_LVL_0, NUM_RCU_LVL_1, NUM_RCU_LVL_2 पूर्ण
#  define RCU_NODE_NAME_INIT  अणु "rcu_node_0", "rcu_node_1", "rcu_node_2" पूर्ण
#  define RCU_FQS_NAME_INIT   अणु "rcu_node_fqs_0", "rcu_node_fqs_1", "rcu_node_fqs_2" पूर्ण
#या_अगर NR_CPUS <= RCU_FANOUT_4
#  define RCU_NUM_LVLS	      4
#  define NUM_RCU_LVL_0	      1
#  define NUM_RCU_LVL_1	      DIV_ROUND_UP(NR_CPUS, RCU_FANOUT_3)
#  define NUM_RCU_LVL_2	      DIV_ROUND_UP(NR_CPUS, RCU_FANOUT_2)
#  define NUM_RCU_LVL_3	      DIV_ROUND_UP(NR_CPUS, RCU_FANOUT_1)
#  define NUM_RCU_NODES	      (NUM_RCU_LVL_0 + NUM_RCU_LVL_1 + NUM_RCU_LVL_2 + NUM_RCU_LVL_3)
#  define NUM_RCU_LVL_INIT    अणु NUM_RCU_LVL_0, NUM_RCU_LVL_1, NUM_RCU_LVL_2, NUM_RCU_LVL_3 पूर्ण
#  define RCU_NODE_NAME_INIT  अणु "rcu_node_0", "rcu_node_1", "rcu_node_2", "rcu_node_3" पूर्ण
#  define RCU_FQS_NAME_INIT   अणु "rcu_node_fqs_0", "rcu_node_fqs_1", "rcu_node_fqs_2", "rcu_node_fqs_3" पूर्ण
#अन्यथा
# error "CONFIG_RCU_FANOUT insufficient for NR_CPUS"
#पूर्ण_अगर /* #अगर (NR_CPUS) <= RCU_FANOUT_1 */

#पूर्ण_अगर /* __LINUX_RCU_NODE_TREE_H */
