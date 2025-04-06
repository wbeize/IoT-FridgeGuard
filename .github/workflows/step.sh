#!/bin/bash
set -ex

echo "This is the value specified for the input 'example_step_input': ${example_step_input}"

#
# --- Export Environment Variables for other Steps:
# You can export Environment Variables for other Steps with
#  envman, which is automatically installed by `bitrise setup`.
# A very simple example:
envman add --key EXAMPLE_STEP_OUTPUT --value 'the value you want to share'
# Envman can handle piped inputs, which is useful if the text you want to
# share is complex and you don't want to deal with proper bash escaping:
#  cat file_with_complex_input | envman add --KEY EXAMPLE_STEP_OUTPUT
# You can find more usage examples on envman's GitHub page
#  at: https://github.com/bitrise-io/envman

#
# --- Exit codes:
# The exit code of your Step is very important. If you return
#  with a 0 exit code `bitrise` will register your Step as "successful".
# Any non zero exit code will be registered as "failed" by `bitrise`.

create_pr() {
	#! If there are conflicts we create a Pull Request
    echo 'conflicts!'

    #! Abort merge
    git merge --abort

    #! Checkout branch we wanted to merge from to create pull request from it
    git checkout $branch_to_merge_from

    #! Create pull request


    PULL_REQUEST=$(gh pr create -B $branch_to_merge_into -t "merge $branch_to_merge_from in $branch_to_merge_into [${GIT_CLONE_COMMIT_MESSAGE_SUBJECT}] [skip ci]" -b "There was an error merging $branch_to_merge_from in $branch_to_merge_into [${GIT_CLONE_COMMIT_MESSAGE_SUBJECT}], please fix the conflict and merge manually. [skip ci]")

    envman add --key CREATED_PULL_REQUEST --value "${PULL_REQUEST}"
    echo "Pull request created at ${PULL_REQUEST}"

    #! Checkout initial branch
    git checkout $branch_to_merge_into

    #! Return failure
    exit 1
}

git fetch

#! Checkout the branch to merge from
git checkout $branch_to_merge_from

#! Checkout the branch to merge into
git checkout $branch_to_merge_into

git merge $branch_to_merge_from || create_pr

echo 'no conflicts'

#! Push merged changes
git push

#! Return success
exit 0

fi