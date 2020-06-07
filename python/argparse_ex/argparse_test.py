import argparse

# parser = argparse.ArgumentParser(description="Process some integers")
# parser.add_argument('integers', metavar='N', type=int, nargs='+',help='an integer for the accumulator')

# parser.add_argument('--sum',dest='accumulate',action='store_const', const=sum, default=max, 
# help='sum the integers (default: find the max')

# args = parser.parse_args()

# print(args.accumulate(args.integers))

parser = argparse.ArgumentParser(description="Cerberus processing")
# parser.add_argument('integers', metavar='N', type=int, nargs='+',help='an integer for the accumulator')
subparsers = parser.add_subparsers(help='cerberus sub-command help')

cerberus_parser = subparsers.add_parser('cerberus', help ='Cerberus help')
cerberus_parser.add_argument('-i', type = int, dest='serverid', required = True, help='serverid')
cerberus_parser.add_argument('-b', type = int, dest='cerberusType', required = True, choices=range(0,2), help='0:cerberus | 1:soc cerbers')
cerberusSubGroup = cerberus_parser.add_argument_group("Cerberus Subcommand")
cerberusSubGroup.add_argument("subcom", choices = ["fwversion", "info", "fwupdatestatus", "pfmid", "pfmversions", "pfmupdatestatus", "pfmrebootaction", "pfmcheckversion",
 "debuglogread", "tcglogread", "pcdid", "pcdupdatestatus", "socgetbootmode", "socfwupdatestatus", "socgetmacid"], type = str)
cerberusSubGroup.add_argument("--pfm_port", dest='pfm_port', type = int, help='pfm_port number')
cerberusSubGroup.add_argument("--pfm_region", dest='pfm_region', type = int, help='pmf_region number')
cerberusSubGroup.add_argument("--ver_string", dest='ver_string', type = int, help='pmf_region number')


# try with mutually exclusive_group
# cerberusSubGroup = cerberus_parser.add_mutually_exclusive_group(required=True)
# cerberusSubGroup.add_argument("")


# cerberusGroup1 = cerberus_parser.add_argument_group("Cerberus Subcommand fwversion")
# cerberusGroup1.add_argument("-s", dest='subcom', type = str, choices = ["fwversion"], help='cerberus fwversion')
# cerberusGroup2 = cerberus_parser.add_argument_group("Soc Cerberus Subcommand info")
# cerberusGroup2.add_argument("-s", dest='subcom', type = str, choices = ["info"], help='cerberus info')
# cerberusGroup3 = cerberus_parser.add_argument_group("Soc Cerberus Subcommand pfmid")
# cerberusGroup3.add_argument("-s", dest='subcom',type = str, choices = ["pfmid"], help=' subcommand pfmid')
# cerberusGroup3.add_argument("pfm_port", type = int, choices = range(0,2), help='pfm_port number')
# cerberusGroup3.add_argument("pfm_region", type = int, choices = range(0,2), help='pfm_region number')




args = parser.parse_args()
# print(args.serverid, args.cerberusType)
print(args.serverid, args.cerberusType, args.subcom)