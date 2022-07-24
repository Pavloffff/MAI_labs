select Surname from pc
WHERE (pc.PNum < 1 OR pc.RAM < 1 OR pc.Vmem < 1 OR pc.DCap < 7 OR pc.ICNum < 1 OR pc.PDNum < 1 OR pc.OS != "Ub") and (
select count(*) as cnt from pc
WHERE (pc.PNum < 1 OR pc.RAM < 1 OR pc.Vmem < 1 OR pc.DCap < 7 OR pc.ICNum < 1 OR pc.PDNum < 1 OR pc.OS != "Ub")
) > 0
