cmd_/home/mal/204/asgn/file-system/Module.symvers := sed 's/\.ko$$/\.o/' /home/mal/204/asgn/file-system/modules.order | scripts/mod/modpost -m -a  -o /home/mal/204/asgn/file-system/Module.symvers -e -i Module.symvers   -T -