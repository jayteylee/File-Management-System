cmd_/home/mal/204/asgn/Module.symvers := sed 's/\.ko$$/\.o/' /home/mal/204/asgn/modules.order | scripts/mod/modpost -m -a  -o /home/mal/204/asgn/Module.symvers -e -i Module.symvers   -T -
