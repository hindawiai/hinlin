<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "tests.h"
#समावेश "machine.h"
#समावेश "thread.h"
#समावेश "debug.h"

पूर्णांक test__thपढ़ो_maps_share(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा machines machines;
	काष्ठा machine *machine;

	/* thपढ़ो group */
	काष्ठा thपढ़ो *leader;
	काष्ठा thपढ़ो *t1, *t2, *t3;
	काष्ठा maps *maps;

	/* other process */
	काष्ठा thपढ़ो *other, *other_leader;
	काष्ठा maps *other_maps;

	/*
	 * This test create 2 processes असलtractions (काष्ठा thपढ़ो)
	 * with several thपढ़ोs and checks they properly share and
	 * मुख्यtain maps info (काष्ठा maps).
	 *
	 * thपढ़ो group (pid: 0, tids: 0, 1, 2, 3)
	 * other  group (pid: 4, tids: 4, 5)
	*/

	machines__init(&machines);
	machine = &machines.host;

	/* create process with 4 thपढ़ोs */
	leader = machine__findnew_thपढ़ो(machine, 0, 0);
	t1     = machine__findnew_thपढ़ो(machine, 0, 1);
	t2     = machine__findnew_thपढ़ो(machine, 0, 2);
	t3     = machine__findnew_thपढ़ो(machine, 0, 3);

	/* and create 1 separated process, without thपढ़ो leader */
	other  = machine__findnew_thपढ़ो(machine, 4, 5);

	TEST_ASSERT_VAL("failed to create threads",
			leader && t1 && t2 && t3 && other);

	maps = leader->maps;
	TEST_ASSERT_EQUAL("wrong refcnt", refcount_पढ़ो(&maps->refcnt), 4);

	/* test the maps poपूर्णांकer is shared */
	TEST_ASSERT_VAL("maps don't match", maps == t1->maps);
	TEST_ASSERT_VAL("maps don't match", maps == t2->maps);
	TEST_ASSERT_VAL("maps don't match", maps == t3->maps);

	/*
	 * Verअगरy the other leader was created by previous call.
	 * It should have shared maps with no change in
	 * refcnt.
	 */
	other_leader = machine__find_thपढ़ो(machine, 4, 4);
	TEST_ASSERT_VAL("failed to find other leader", other_leader);

	/*
	 * Ok, now that all the rbtree related operations were करोne,
	 * lets हटाओ all of them from there so that we can करो the
	 * refcounting tests.
	 */
	machine__हटाओ_thपढ़ो(machine, leader);
	machine__हटाओ_thपढ़ो(machine, t1);
	machine__हटाओ_thपढ़ो(machine, t2);
	machine__हटाओ_thपढ़ो(machine, t3);
	machine__हटाओ_thपढ़ो(machine, other);
	machine__हटाओ_thपढ़ो(machine, other_leader);

	other_maps = other->maps;
	TEST_ASSERT_EQUAL("wrong refcnt", refcount_पढ़ो(&other_maps->refcnt), 2);

	TEST_ASSERT_VAL("maps don't match", other_maps == other_leader->maps);

	/* release thपढ़ो group */
	thपढ़ो__put(leader);
	TEST_ASSERT_EQUAL("wrong refcnt", refcount_पढ़ो(&maps->refcnt), 3);

	thपढ़ो__put(t1);
	TEST_ASSERT_EQUAL("wrong refcnt", refcount_पढ़ो(&maps->refcnt), 2);

	thपढ़ो__put(t2);
	TEST_ASSERT_EQUAL("wrong refcnt", refcount_पढ़ो(&maps->refcnt), 1);

	thपढ़ो__put(t3);

	/* release other group  */
	thपढ़ो__put(other_leader);
	TEST_ASSERT_EQUAL("wrong refcnt", refcount_पढ़ो(&other_maps->refcnt), 1);

	thपढ़ो__put(other);

	machines__निकास(&machines);
	वापस 0;
पूर्ण
